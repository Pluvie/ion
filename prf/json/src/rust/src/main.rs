use std::fs;
use serde::Deserialize;

#[derive(Deserialize)]
#[derive(Debug)]
struct User {
  name: String,
  age: u32,
  roles: Vec<String>,
}

#[derive(Deserialize)]
struct Data {
  users: Vec<User>,
}

fn main() {
  let json = fs::read_to_string("exe/decode.json").expect("cannot read exe/decode.json");
  let data: Data = serde_json::from_str(&json).unwrap();

  println!("Done:{:?}\n", data.users.get(0));
  println!("Done:{:?}\n", data.users.get(9999999));
  println!("Done:{:?}\n", data.users.get(10000000));
}
