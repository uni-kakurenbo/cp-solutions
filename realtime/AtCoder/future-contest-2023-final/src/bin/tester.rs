#![allow(non_snake_case)]

use rand::prelude::*;
use std::fmt::Display;
use std::io::{prelude::*, BufReader};
use std::process::{ChildStdout, Stdio};
use std::str::FromStr;
use tools::*;

fn read(stdout: &mut BufReader<ChildStdout>) -> Result<String, String> {
    loop {
        let mut out = String::new();
        match stdout.read_line(&mut out) {
            Ok(0) | Err(_) => {
                return Err(format!("Your program has terminated unexpectedly"));
            }
            _ => (),
        }
        print!("{}", out);
        let v = out.trim();
        if v.len() == 0 || v.starts_with("#") {
            continue;
        }
        return Ok(v.to_owned());
    }
}

fn parse_bounded<T: FromStr + PartialOrd + Display>(v: &str, lb: T, ub: T) -> Result<T, String> {
    let v = v.parse::<T>().map_err(|_| format!("Illegal output: {}", v))?;
    if v < lb || ub < v {
        return Err(format!("Illegal output: {}", v));
    }
    Ok(v)
}

fn exec(p: &mut std::process::Child) -> Result<i64, String> {
    let mut input = String::new();
    std::io::stdin().read_to_string(&mut input).unwrap();
    let input = parse_input(&input);
    let mut stdin = std::io::BufWriter::new(p.stdin.take().unwrap());
    let mut stdout = std::io::BufReader::new(p.stdout.take().unwrap());
    let _ = writeln!(stdin, "{:.3}", input.sigma);
    let _ = stdin.flush();
    let mut rng = rand_chacha::ChaCha20Rng::seed_from_u64(input.seed);
    let normal = rand_distr::Normal::new(0.0, input.sigma).unwrap();
    let mut done = vec![false; input.ps.len()];
    let mut F = 0;
    for t in 0..Q {
        let s = read(&mut stdout)?;
        let xy = s.split_whitespace().collect::<Vec<_>>();
        if xy.len() != 2 {
            return Err(format!("Illegal output: {}", s));
        }
        let x = parse_bounded(xy[0], -R, R)?;
        let y = parse_bounded(xy[1], -R, R)?;
        if x * x + y * y > R * R {
            return Err(format!("Illegal output: {}", s));
        }
        if let Some(i) = (0..input.ps.len()).find(|&i| !done[i] && dist2(input.ps[i], (x, y)) <= D * D) {
            done[i] = true;
            F += 1;
            if F == input.ps.len() {
                println!("#r 2 {} {}", input.ps[i].0, input.ps[i].1);
                let _ = writeln!(stdin, "2 {} {}", input.ps[i].0, input.ps[i].1);
                let _ = stdin.flush();
                p.wait().unwrap();
                return Ok(score(F, t + 1));
            } else {
                println!("#r 1 {} {}", input.ps[i].0, input.ps[i].1);
                let _ = writeln!(stdin, "1 {} {}", input.ps[i].0, input.ps[i].1);
                let _ = stdin.flush();
            }
        } else {
            let i = *(0..input.ps.len())
                .filter(|&i| !done[i])
                .collect::<Vec<_>>()
                .choose_weighted(&mut rng, |&i| 1.0 / dist2(input.ps[i], (x, y)) as f64)
                .unwrap();
            let mut dir = f64::atan2((input.ps[i].1 - y) as f64, (input.ps[i].0 - x) as f64);
            dir += rng.sample(normal);
            dir %= 2.0 * std::f64::consts::PI;
            if dir < 0.0 {
                dir += 2.0 * std::f64::consts::PI;
            }
            println!("#r 0 {:.10}", dir);
            let _ = writeln!(stdin, "0 {:.10}", dir);
            let _ = stdin.flush();
        };
    }
    Ok(score(F, Q))
}

fn main() {
    if std::env::args().len() < 2 {
        eprintln!("Usage: {} <command> [<args>...]", std::env::args().nth(0).unwrap());
        return;
    }
    let (command, args) = (std::env::args().nth(1).unwrap(), std::env::args().skip(2).collect::<Vec<_>>());
    let mut p = std::process::Command::new(command)
        .args(args)
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .spawn()
        .unwrap_or_else(|e| {
            eprintln!("failed to execute the command");
            eprintln!("{}", e);
            std::process::exit(1)
        });
    match exec(&mut p) {
        Ok(score) => {
            p.wait().unwrap();
            eprintln!("Score = {}", score);
        }
        Err(err) => {
            if let Ok(Some(status)) = p.try_wait() {
                if !status.success() {
                    std::process::exit(1);
                }
            }
            let _ = p.kill();
            eprintln!("{}", err);
            eprintln!("Score = 0");
        }
    }
}
