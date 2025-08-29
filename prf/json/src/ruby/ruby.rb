require "json"

data = JSON.parse(File.read("exe/decode.json"))

puts data[0]
puts data[9999999]
puts data[10000000]
