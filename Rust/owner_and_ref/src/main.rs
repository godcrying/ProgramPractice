fn main() {
    let s = String::from("hello");
    
    takes_ownership(s); 
    // 字符串进入函数的作用域时，所有权交给函数中的s。
    // 即字符串数据move到函数内，函数外的s失效。
    // 在离开函数作用域时，因为函数没有返回值，故字符串在此时销毁。
    // 所有权原则之一：变量在离开作用域时其值被销毁。
    // 此时s已经无效，再调用s会报错。
    // println!("{}", s);

    let x = 5;
    makes_copy(x);
}

fn takes_ownership(some_string: String) {
    println!("{}", some_string);    
}

fn makes_copy(some_integer: i32) {
    println!("{}", some_integer);    
}
