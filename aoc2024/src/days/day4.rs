use std::{
    fs::File,
    io::{BufReader, Lines},
    time::Instant,
};

pub fn run(lines: Lines<BufReader<File>>) {
    let mut m = Vec::new();

    for line in lines.flatten() {
        let line: Vec<char> = line.chars().collect();
        m.push(line);
    }

    let now = Instant::now();
    println!("Part 1: {}", part1(&m));
    let elapsed = now.elapsed();
    println!("Elapsed: {:.2?}", elapsed);

    let now = Instant::now();
    println!("Part 2: {}", part2(&m));
    let elapsed = now.elapsed();
    println!("Elapsed: {:.2?}", elapsed);
}

fn part1(m: &Vec<Vec<char>>) -> u32 {
    let mut res = 0;
    let xmas = "XMAS";
    let r_xmas = "SAMX";

    let mut rows = vec![String::new(); m.len()];
    let mut cols = vec![String::new(); m.len()];
    let mut d1 = vec![String::new(); 2 * (2 * m.len() - 1)];
    let mut d2 = vec![String::new(); 2 * (2 * m.len() - 1)];
    let mut total = vec![];

    // build rows, cols and diagonals
    for r in 0..m.len() {
        for c in 0..m.len() {
            rows[r].push(m[r][c]);
            cols[c].push(m[r][c]);
            d1[r + c].push(m[r][c]);
            d2[m.len() + r - c].push(m[r][c]);
        }
    }

    total.append(&mut rows);
    total.append(&mut cols);
    total.append(&mut d1);
    total.append(&mut d2);

    for t in total {
        res += t.matches(xmas).count();
        res += t.matches(r_xmas).count();
    }

    res.try_into().unwrap()
}

fn part2(m: &Vec<Vec<char>>) -> u32 {
    let mut res = 0;
    let mas = "MAS";
    let r_mas = "SAM";
    for r in 1..m.len() - 1 {
        for c in 1..m.len() - 1 {
            if m[r][c] != 'A' {
                continue;
            }
            let d1 = format!("{}A{}", m[r-1][c-1], m[r+1][c+1]);
            let d2 = format!("{}A{}", m[r+1][c-1], m[r-1][c+1]);
            if (d1 != mas && d1 != r_mas) || (d2 != mas && d2 != r_mas) {
                continue;
            }
            res += 1;
        }
    }
    res
}
