pub mod sysinfo {
    pub mod cpu;
    pub mod distro;
    pub mod host;
    pub mod kernel;
    pub mod ram;
}
use crate::sysinfo::cpu;
use crate::sysinfo::distro;
use crate::sysinfo::host;
use crate::sysinfo::kernel;
use crate::sysinfo::ram;

fn main() {
    // TODO: add host::get_host();
    println!("cpu: {}", cpu::get_cpu());
    println!("distro: {}", distro::get_distro());
    println!("distro id: {}", distro::get_distro_id());
    println!("hostname: {}", host::get_hostname());
    println!("kernel: {}", kernel::get_kernel_version());
    println!("ram: {}", ram::get_memory_usage());
}
