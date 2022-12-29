#![allow(non_snake_case, unused_macros)]

use proconio::input;
use rand::prelude::*;

pub trait SetMinMax {
    fn setmin(&mut self, v: Self) -> bool;
    fn setmax(&mut self, v: Self) -> bool;
}
impl<T> SetMinMax for T
where
    T: PartialOrd,
{
    fn setmin(&mut self, v: T) -> bool {
        *self > v && {
            *self = v;
            true
        }
    }
    fn setmax(&mut self, v: T) -> bool {
        *self < v && {
            *self = v;
            true
        }
    }
}

#[macro_export]
macro_rules! mat {
	($($e:expr),*) => { Vec::from(vec![$($e),*]) };
	($($e:expr,)*) => { Vec::from(vec![$($e),*]) };
	($e:expr; $d:expr) => { Vec::from(vec![$e; $d]) };
	($e:expr; $d:expr $(; $ds:expr)+) => { Vec::from(vec![mat![$e $(; $ds)*]; $d]) };
}

pub const Q: usize = 1000;
pub const N: usize = 50;
pub const R: i64 = 1000000000;
pub const D: i64 = 1000000;

#[derive(Clone, Debug)]
pub struct Input {
    pub sigma: f64,
    pub ps: Vec<(i64, i64)>,
    pub seed: u64,
}

impl std::fmt::Display for Input {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "{:.3}", self.sigma)?;
        for i in 0..self.ps.len() {
            writeln!(f, "{} {}", self.ps[i].0, self.ps[i].1)?;
        }
        writeln!(f, "{}", self.seed)?;
        Ok(())
    }
}

pub fn parse_input(f: &str) -> Input {
    let f = proconio::source::once::OnceSource::from(f);
    input! {
        from f,
        sigma: f64,
        ps: [(i64, i64); N],
        seed: u64,
    }
    Input { sigma, ps, seed }
}

pub struct Output {
    pub qs: Vec<(i64, i64)>,
    pub comments: Vec<String>,
    pub responses: Vec<String>,
    pub colors: Vec<Vec<(i32, i32, u8, u8, u8)>>,
    pub found: Vec<i32>,
    pub scores: Vec<i64>,
}

pub fn parse_output(input: &Input, f: &str) -> Result<Output, String> {
    let tokens = f.lines();
    let mut qs = vec![];
    let mut comment = String::new();
    let mut comments = vec![];
    let mut responses = vec![];
    let mut colors = vec![vec![]];
    let mut found = vec![Q as i32; N];
    let mut scores = vec![0];
    let mut F = 0;
    let mut rng = rand_chacha::ChaCha20Rng::seed_from_u64(input.seed);
    let normal = rand_distr::Normal::new(0.0, input.sigma).unwrap();
    for v in tokens {
        let v = v.trim();
        if v.len() == 0 {
            continue;
        } else if v.starts_with("#") {
            if v.starts_with("#r ") {
                if responses.len() == qs.len() {
                    return Err(format!("Duplicated #r (turn {})", qs.len() - 1));
                }
                responses.push(v["#r ".len()..].trim().to_owned());
            } else if v.starts_with("#c ") {
                let vs = v.split_whitespace().collect::<Vec<_>>();
                if vs.len() != 6 {
                    return Err(format!("Illegal #c: {}", v));
                }
                let x = vs[1].parse::<i32>().map_err(|_| format!("Illegal #c: {}", v))?;
                let y = vs[2].parse::<i32>().map_err(|_| format!("Illegal #c: {}", v))?;
                let r = vs[3].parse::<u8>().map_err(|_| format!("Illegal #c: {}", v))?;
                let g = vs[4].parse::<u8>().map_err(|_| format!("Illegal #c: {}", v))?;
                let b = vs[5].parse::<u8>().map_err(|_| format!("Illegal #c: {}", v))?;
                colors.last_mut().unwrap().push((x, y, r, g, b));
            } else {
                comment += v;
                comment.push('\n');
            }
        } else {
            let xy = v.split_whitespace().collect::<Vec<_>>();
            if xy.len() != 2 {
                return Err(format!("Illegal output (turn {})", qs.len()));
            }
            if qs.len() > 0 {
                if let Some(i) = (0..N).find(|&i| found[i] == qs.len() as i32 - 1) {
                    if responses.len() != qs.len() {
                        responses.push(format!("{} {} {}", if F == N { 2 } else { 1 }, input.ps[i].0, input.ps[i].1));
                    }
                } else {
                    let (x, y) = qs[qs.len() - 1];
                    let i = *(0..input.ps.len())
                        .filter(|&i| found[i] == Q as i32)
                        .collect::<Vec<_>>()
                        .choose_weighted(&mut rng, |&i| 1.0 / dist2(input.ps[i], (x, y)) as f64)
                        .unwrap();
                    let mut dir = f64::atan2((input.ps[i].1 - y) as f64, (input.ps[i].0 - x) as f64);
                    dir += rng.sample(normal);
                    dir %= 2.0 * std::f64::consts::PI;
                    if dir < 0.0 {
                        dir += 2.0 * std::f64::consts::PI;
                    }
                    if responses.len() != qs.len() {
                        responses.push(format!("0 {:.10}", dir));
                    }
                }
            }
            let x = xy[0]
                .parse::<i64>()
                .map_err(|_| format!("Illegal output (turn {})", qs.len()))?;
            let y = xy[1]
                .parse::<i64>()
                .map_err(|_| format!("Illegal output (turn {})", qs.len()))?;
            qs.push((x, y));
            if x.abs() > R || y.abs() > R || x * x + y * y > R * R {
                return Err(format!("Illegal output (turn {})", qs.len()));
            }
            comments.push(comment);
            comment = String::new();
            for i in 0..N {
                if found[i] == Q as i32 && dist2((x, y), input.ps[i]) <= D * D {
                    found[i] = qs.len() as i32 - 1;
                    F += 1;
                }
            }
            scores.push(score(F, qs.len()));
            colors.push(vec![]);
        }
    }
    if qs.len() > Q {
        return Err(format!("Too many outputs"));
    }
    if responses.len() != qs.len() {
        if let Some(i) = (0..N).find(|&i| found[i] == qs.len() as i32 - 1) {
            responses.push(format!("{} {} {}", if F == N { 2 } else { 1 }, input.ps[i].0, input.ps[i].1));
        } else {
            let (x, y) = qs[qs.len() - 1];
            let i = *(0..input.ps.len())
                .filter(|&i| found[i] == Q as i32)
                .collect::<Vec<_>>()
                .choose_weighted(&mut rng, |&i| 1.0 / dist2(input.ps[i], (x, y)) as f64)
                .unwrap();
            let mut dir = f64::atan2((input.ps[i].1 - y) as f64, (input.ps[i].0 - x) as f64);
            dir += rng.sample(normal);
            dir %= 2.0 * std::f64::consts::PI;
            if dir < 0.0 {
                dir += 2.0 * std::f64::consts::PI;
            }
            responses.push(format!("0 {:.10}", dir));
        }
    }
    Ok(Output {
        qs,
        comments,
        responses,
        colors,
        found,
        scores,
    })
}

pub fn dist2(p: (i64, i64), q: (i64, i64)) -> i64 {
    let dx = p.0 - q.0;
    let dy = p.1 - q.1;
    dx * dx + dy * dy
}

pub fn score(F: usize, k: usize) -> i64 {
    if F < N {
        (0.5 * 1e4 * F as f64 / N as f64).round() as i64
    } else {
        (1e4 * (1.0 - 0.5 * k as f64 / Q as f64)).round() as i64
    }
}

pub fn gen(seed: u64, custom_sigma: Option<f64>) -> Input {
    let mut rng = rand_chacha::ChaCha20Rng::seed_from_u64(seed);
    let mut sigma = rng.gen_range(1, 101) as f64 * 0.001;
    if let Some(c) = custom_sigma {
        sigma = c;
    }
    let mut ps = vec![];
    while ps.len() < N {
        let x = rng.gen_range(-R, R + 1);
        let y = rng.gen_range(-R, R + 1);
        if x * x + y * y <= R * R {
            let mut ok = true;
            for &q in &ps {
                ok &= dist2(q, (x, y)) > 4 * D * D;
            }
            if ok {
                ps.push((x, y));
            }
        }
    }
    let seed = rng.gen::<u64>();
    Input { sigma, ps, seed }
}

pub fn compute_score(_input: &Input, output: &Output) -> i64 {
    *output.scores.last().unwrap()
}
