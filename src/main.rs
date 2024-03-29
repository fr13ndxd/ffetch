pub mod sysinfo {
    pub mod cpu;
}
use crate::sysinfo::cpu;

fn main() {
    //println!("cpu: {}", cpu::get_cpu());
    cpu::get_cpu();
}
