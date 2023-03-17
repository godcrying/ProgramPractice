use std::fmt;

#[derive(PartialEq,Copy, Clone)]
pub enum Color {
    Red,
    Green,
    Blue,
    None,
}

impl fmt::Display for Color {
   fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
       let str = match self {
           &Color::Red => "Red",
           &Color::Green => "Green",
           &Color::Blue => "Blue",
           _ => "NAC",
       };
       write!(f, "{}", str)
    }
}

pub struct Node {
    color:Color,
    name:String,
    arclist:Vec<usize>,
}

pub struct Map {
    // node_num:u32,
    // arc_num:u32,
    nodelist:Vec<Node>,
}

impl Map {
    pub fn create_map() -> Map {
        let mut m:Map = Map {
            // node_num:7,
            // arc_num:18,
            nodelist:Vec::new(),
        };
        let region = ["WA","NT","SA","Q","NSW","V","T"];
        let links = [[0,2],[0,1],[1,0],[1,2],[1,3],[2,0],[2,1],[2,3],[2,4],
        [2,5],[3,1],[3,2],[3,4],[4,2],[4,3],[4,5],[5,2],[5,4]];
        for &name in region.iter() {
            let node = Node {
                name:String::from(name),
                color:Color::None,
                arclist:Vec::new(),
            };
            m.nodelist.push(node);
        }

        for link in links.iter() {
            let node = &mut m.nodelist.get_mut(link[0]).unwrap();
            node.arclist.push(link[1]);
        }
        m
    }

    pub fn print_map(&self) {
        for node in self.nodelist.iter() {
            println!("NodeName:{}\tNodeColor:{}",node.name,node.color);
        }
    }

    pub fn select_node(&self) -> Option<usize> {
        for (index,node) in self.nodelist.iter().enumerate() {
            if let Color::None = node.color {
                println!("find a node:{}",index);
                return Some(index);
            }
        }
        None
    }

    fn interfere(&self,index:usize,c:&Color) -> bool {
        let node = self.nodelist.get(index).unwrap();
        for neig in node.arclist.iter() {
            if *c == self.nodelist.get(*neig).unwrap().color {
                return false;
            }
        }
        true
    }

    fn backtrace(&mut self) {
        if let Some(index) = self.select_node() {
            for color in [Color::Red,Color::Green,Color::Blue].iter() {
                if self.interfere(index, color) {
                    self.nodelist.get_mut(index).unwrap().color = *color;
                    println!("{}",color);
                    self.backtrace();
                    break;
                }
            }
        }
    }
}


fn main() {
    println!("Hello, world!");

    let mut a_map = Map::create_map();
    println!("-----------------");
    println!("Map Information");
    println!("-----------------");
    a_map.print_map();
    a_map.backtrace();
    println!("-----------------");
    println!("Map Color");
    println!("-----------------");
    a_map.print_map();
}
