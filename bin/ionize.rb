module Ion

  ##
  # Finds the start index of a common prefix between two strings, from their beginning.
  # If no common prefix is present -- i.e. the strings start with a different character
  # -- returns 0.
  def common_prefix_start(str1, str2)
    return "" if str1.empty? || str2.empty?
    result = 0
    (0...[str1.length, str2.length].min).each do |k|
      if str1[k] == str2[k]
        result += 1
      else
        break
      end
    end
    result
  end
  
  ##
  # Checks if the file is unchanged from the last iteration.
  # Returns false if the file does not exists.
  def file_is_unchanged?(source, target)
    return false if not File.file?(target)
    return File.mtime(target) > File.mtime(source)
  end

  ##
  # Normalizes the type.
  def normalize_type(type)
    type
      .gsub(/[\s]*,[\s]*/, ", ")
      .gsub(/[\s]*\*[\s]*/, "*")
      .gsub(/[\s]+/, ' ')
  end
  
  ##
  # Inflects the Ion container type, i.e. `list<char*>` becomes `list_char_p`.
  def inflect_type(normalized_type)
    normalized_type
      .gsub(/[,\s]/, '_')
      .gsub(/\*/, "_p")
  end
  
  ##
  # Ionizes the file, which means finding all Ion type containers, and inflecting their
  # name. Just that.
  def ionize_file(source, target)
    types = Set.new
    source = File.expand_path(source)
    target ||= source
    content = File.read(source)
    content.gsub!(/([A-z][A-z_]+)(<[A-z][A-z0-9_,\* ]+>)/) do |match|
      container, type = match[..-2].split('<')
      normalized_type = normalize_type(type)
      types << [ container, normalized_type ]
      "#{container}_#{inflect_type(normalized_type)}"
    end
    File.write(target, content)
    types
  end

  ##
  # Ionizes the directory, transferring only files that have been modified to a safe
  # place where they can be ionized individually.
  def ionize_directory(source, target)
    source = File.expand_path(source)
    target ||= File.join(Dir.home, ".ion")
    prefix_start = common_prefix_start(source, target)
    target_dir = File.join(target, source[prefix_start..])
    target_existing = Set.new(Dir.glob(File.join(target_dir, "**", "*.{c,h}")))
    types = Set.new

    # For each source file in the source directory, finds its target path, creates the
    # directory if not present, and ionizes the file. Skips files that have not changed
    # since the last iteration. Every processed file -- ionized or not -- is then removed
    # from the `target_existing` global variable, to track files that aren't present
    # anymore in the target directory.
    Dir.glob(File.join(source, "**", "*.{c,h}")) do |file|
      relative_file = file[source.length+1..]
      target_file = File.join(target_dir, relative_file)
      target_dir_path = File.dirname(target_file)
      target_existing.delete(target_file)
      FileUtils.mkdir_p(target_dir_path)
      next if file_is_unchanged?(file, target_file)
      types |= ionize_file(file, target_file)
    end

    File.write(File.join(target_dir, "containers.h"),
      types.map do |container, type|
        "#define #{container}_of #{type}\n#include \"ion/containers/#{container}.h\""
      end.join("\n"))
    File.write(File.join(target_dir, "containers.c"),
      types.map do |container, type|
        "#define #{container}_of #{type}\n#include \"ion/containers/#{container}.c\""
      end.join("\n"))

    # Deletes obsolete files in the target directory.
    target_existing.each do |file|
      File.delete(file)
    end

    # Returns the target directory, which can be used in subsequent compilation steps.
    print(target_dir)
  end

end



include Ion
require "fileutils"

if ARGV.length < 2
  puts "Usage: ionize [--file|--file-list|--directory] source [target]"
  exit 1
end

operation = ARGV[0]
case operation
when "--file"
  ionize_file ARGV[1], ARGV[2]
when "--file-list"
  list = ARGV[1].split(" ")
  list.each do |file|
    ionize_file file, file
  end
when "--directory"
  ionize_directory ARGV[1], ARGV[2]
else
  puts "Usage: ionize [--file|--directory] source [target]"
  exit 1
end

