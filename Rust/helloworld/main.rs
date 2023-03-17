fn main() {
    let s = String::from("helloworld");
    let q = String::from("thankyou");
    
    let s2 = test(&s);
    println!("{}", s2);
}

fn test(s:&String) -> &String {
    &s    
}
