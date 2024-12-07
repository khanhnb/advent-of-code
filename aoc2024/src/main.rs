use std::{env, process};

use aoc2024::{run, Config};

fn main() {
    println!("cargo run -- [day-number] [input-data]");
    let args: Vec<String> = env::args().collect();
    let cfg = Config::build(&args).unwrap_or_else(|err| {
        println!("Problem parsing arguments: {err}");
        process::exit(1);
    });

    if let Err(e) = run(cfg) {
        println!("Application error: {e}");
        process::exit(1);
    }
}

