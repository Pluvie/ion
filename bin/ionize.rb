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



if ARGV.length < 1
  puts "Usage: ionize source [target]"
  exit 1
end

source = File.expand_path(ARGV[0])
target = ARGV[1] || $source
ionize_file(source, target)
