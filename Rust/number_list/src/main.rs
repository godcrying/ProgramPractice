use std::collections::HashMap;

fn main() {
    let v = vec![53,62,89,45,12,3,77,99,62,88,62,45,77,76,32];
    let avg = get_average(&v);
    let mid = get_mid(&v);
    let most = get_most(&v);

    println!("average is {}", avg);
    println!("mid is {}", mid);
    println!("most is {}", most);
}

fn get_average(v:&Vec<i32>) -> i32 {
    let mut sum = 0;
    let count  = v.len() as i32;
    for i in v {
        sum += i;
    }

    sum/count
}

fn get_mid(v:&Vec<i32>) -> i32 {
    let mut tmp_v = v.clone();
    tmp_v.sort();
    let count = tmp_v.len();
   println!("{:?}", tmp_v); 
    tmp_v[count/2]
}

fn get_most(v:&Vec<i32>) -> i32 {
    let mut tab: HashMap<i32,i32> = HashMap::new();
    for num in v {
        let count = tab.entry(*num).or_insert(0);
        *count += 1;
    }
    println!("{:?}", tab);
    let mut most = 0;
    let mut max_count = 0;
    for (key,value) in tab {
        if value > max_count {
            max_count = value;
            most = key;
        }
    }
    most
}
