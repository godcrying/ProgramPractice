fn main() {
    let s1 = String::from("Hello,");
    let s2 = String::from("world!");
    let mut s3 = s1 + &s2; 
    //使用"+"连接字符串，前面的对象必须是String类型，而不能是引用类型
    //此处若使用 &s1 则会报错。
    
    let s4 = "123";
    s3.push_str(s4);
     
    let s4 = &s3;
    test(s4);//因为引用没有所有权概念，所以此处不会使s4失效，因为s4是一个引用。
    
    println!("{}", s4);

    for c in "你好，世界！".chars() {
        println!("{}", c);    
    }
    
    for c in "你好，世界！".bytes() {
        println!("{}", c);    
    }

}

fn test(some_str: &String) {
    println!("{} 在test中", some_str);    
}
