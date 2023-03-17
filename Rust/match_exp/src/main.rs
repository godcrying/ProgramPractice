#[derive(Debug)]
enum UsState {
    Alabama,
    Alaska,    
}
enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter(UsState),    
}

fn value_in_cents(coin: Coin) -> u32 {
      match coin {
          Coin::Penny => 1,
          Coin::Nickel => 5,
          Coin::Dime => 10,
          Coin::Quarter(state) => {
              println!("State quarter from {:?}!", state);
              25
          },
      }
}
       

fn main() {

    let coin = Coin::Quarter(UsState::Alaska);

    let value = value_in_cents(coin);

    println!("{}", value);
    
    // let coin2 = coin; coin已经被move到value_in_cents()中了。
        
}
