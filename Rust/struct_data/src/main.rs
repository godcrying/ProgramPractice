
struct User {
    username: String,
    email: String,
    sign_in_count: u64,
    active: bool,
    location: String,  
}

fn main() {
    let mut user1 = User {
        email: String::from("someone@example.com"),
        username: String::from("Someone"),
        active: true,
        sign_in_count: 1,
        location: String::from("beijing"),
    };

    let user2 = User {
        email: String::from("another@exp.com"),
        username: String::from("another"),
        ..user1 
    };

    user1.location = String::from("xiaan");

    println!("user1's name is {}", user1.username);
    println!("user2's location is {}", user2.location);
}
