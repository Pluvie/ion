use std::collections::HashMap;

fn main() {
    let mut map: HashMap<i32, i32> = HashMap::new();
    for i in 1..1000000 {
      map.insert(i, i);
    }

    // Step 2: Get value from HashMap.
    println!("Done: {}", map.get(&999999).unwrap());
}
