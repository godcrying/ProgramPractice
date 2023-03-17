fn main() {
    let mut v = Vec::new();

    v.push(5);
    v.push(6);
    v.push(7);
    v.push(8);

    for elem in &v {
        println!("{}", elem);
    }

    v.push(9);
    v.pop();
    let x = v.pop();
    if let Some(i) = x {
        println!("{}", i);    
    }
}
