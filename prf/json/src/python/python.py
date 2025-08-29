import json

with open("exe/decode.json") as file:
  data = json.loads(file.read())

print(data["users"][0])
print(data["users"][9999999])
print(data["users"][10000000])
