use std::{
    fs::File,
    io::{BufReader, Lines},
    time::Instant,
};

use regex::Regex;

pub fn run(lines: Lines<BufReader<File>>) {
    let mut l = Vec::new();
    for line in lines {
        l.push(line.unwrap());
    }

    let now = Instant::now();
    println!("Part 1: {}", part1(&l));
    let elapsed = now.elapsed();
    println!("Elapsed: {:.2?}", elapsed);

    let now = Instant::now();
    println!("Part 2: {}", part2(&l));
    let elapsed = now.elapsed();
    println!("Elapsed: {:.2?}", elapsed);
}

fn part1(lines: &Vec<String>) -> u32 {
    let mut res = 0;
    let regex = Regex::new(r"(?m)mul\((\d+),(\d+)\)").unwrap();
    for line in lines {
        let result = regex.captures_iter(line);
        for mat in result {
            res += mat[1].parse::<u32>().unwrap() * mat[2].parse::<u32>().unwrap();
        }
    }
    res
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Instruction {
    Do(usize),
    Dont(usize),
    Mul(usize, u32, u32),
}

impl Instruction {
    fn ins_index(&self) -> usize {
        match *self {
            Instruction::Do(index) => index,
            Instruction::Dont(index) => index,
            Instruction::Mul(index, _, _) => index,
        }
    }
}

impl Ord for Instruction {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.ins_index().cmp(&other.ins_index())
    }
}

impl PartialOrd for Instruction {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(&other))
    }
}

fn part2(lines: &Vec<String>) -> u32 {
    let mut res = 0;
    // first instruction is enabled by default
    let mut enable = true;
    for line in lines {
        let mut ins: Vec<Instruction> = Vec::new();
        // add do() ins
        let regex = Regex::new(r"(?m)do\(\)").unwrap();
        let result = regex.captures_iter(line);
        for mat in result {
            ins.push(Instruction::Do(mat.get(0).unwrap().start()));
        }
        // add dont() ins
        let regex = Regex::new(r"(?m)don't\(\)").unwrap();
        let result = regex.captures_iter(line);
        for mat in result {
            ins.push(Instruction::Dont(mat.get(0).unwrap().start()));
        }
        // add mul ins
        let regex = Regex::new(r"(?m)mul\((\d+),(\d+)\)").unwrap();
        let result = regex.captures_iter(line);
        for mat in result {
            ins.push(Instruction::Mul(
                mat.get(0).unwrap().start(),
                mat[1].parse::<u32>().unwrap(),
                mat[2].parse::<u32>().unwrap(),
            ));
        }
        ins.sort();
        for i in ins {
            match i {
                Instruction::Do(_) => {
                    enable = true;
                }
                Instruction::Dont(_) => {
                    enable = false;
                }
                Instruction::Mul(_, first, second) => {
                    if enable {
                        res += first * second;
                    }
                }
            }
        }
    }
    res
}
