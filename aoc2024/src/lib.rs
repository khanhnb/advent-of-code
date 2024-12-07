use std::io::{self, BufRead};
use std::{error::Error, fs::File, path::Path};

mod days;

pub struct Config {
    pub day: String,
    pub input_path: String,
}

impl Config {
    pub fn build(args: &[String]) -> Result<Config, &str> {
        if args.len() < 3 {
            return Err("Not enough args");
        }
        let query = args[1].clone();
        let file_path = args[2].clone();

        Ok(Config {
            day: query,
            input_path: file_path,
        })
    }
}
pub fn run(cfg: Config) -> Result<(), Box<dyn Error>> {
    if let Ok(lines) = read_lines(&cfg.input_path) {
        match cfg.day.as_str() {
            "1" => days::day1::run(lines),
            "2" => days::day2::run(lines),
            "3" => days::day3::run(lines),
            "4" => days::day4::run(lines),
            "5" => days::day5::run(lines),
            _ => println!("Day not implemented"),
        }
    } else {
        println!("file: {} not found", &cfg.input_path);
    }
    Ok(())
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}
