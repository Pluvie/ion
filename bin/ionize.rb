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
  # Inflects the Ion container type, i.e. `list<char*>` becomes `list_char_p`.
  def inflect_type(type)
    type
      .gsub(/[ ]*,[ ]*/, '_')
      .gsub(/[ ]*\*/, "_p")
      .gsub(/[ ]+/, '_')
  end
  
  ##
  # Ionizes the file, which means finding all Ion type containers, and inflecting their
  # name. Just that.
  def ionize_file(source, target)
    content = File.read(source)
    content.gsub!(/([A-z][A-z_]+)(<[A-z][A-z0-9_,\* ]+>)/) do |match|
      container, type = match[..-2].split('<')
      "#{container}_#{inflect_type(type)}"
    end
    File.write(target, content)
  end

end



if ARGV.length < 1
  puts "Usage: ionize source_dir [output_dir]"
  exit 1
end

include Ion
require "fileutils"

$source = File.expand_path(ARGV[0])
$target = ARGV[1] || File.join(Dir.home, ".ion")
prefix_start = common_prefix_start($source, $target)
$target_dir = File.join($target, $source[prefix_start..])
$target_existing = Set.new(Dir.glob(File.join($target_dir, "**", "*.{c,h}")))

# For each source file in the source directory, finds its target path, creates the
# directory if not present, and ionizes the file. Skips files that have not changed
# since the last iteration. Every processed file -- ionized or not -- is then removed
# from the `$target_existing` global variable, to track files that aren't present
# anymore in the target directory.
Dir.glob(File.join($source, "**", "*.{c,h}")) do |file|
  relative_file = file[$source.length+1..]
  target_file = File.join($target_dir, relative_file)
  target_dir = File.dirname(target_file)
  $target_existing.delete(target_file)
  FileUtils.mkdir_p(target_dir)
  next if file_is_unchanged?(file, target_file)
  ionize_file(file, target_file)
end

# Deletes obsolete files in the target directory.
$target_existing.each do |file|
  File.delete(file)
end

# Returns the target directory, which can be used in subsequent compilation steps.
print($target_dir)
