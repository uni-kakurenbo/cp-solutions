#![allow(non_snake_case, unused_macros)]

use proconio::input;
use rand::prelude::*;
use std::ops::RangeBounds;
use svg::node::element::Style;
use std::collections::{BTreeMap, HashSet};

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

#[derive(Clone, Debug)]
pub struct Input {
    n: usize,
    a: Vec<i64>,
    b: Vec<i64>,
}

impl std::fmt::Display for Input {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "{}", self.n)?;
        for (x, y) in self.a.iter().zip(self.b.iter()) {
            writeln!(f, "{} {}", x, y)?;
        }
        Ok(())
    }
}

pub fn parse_input(f: &str) -> Input {
    let f = proconio::source::once::OnceSource::from(f);
    input! {
        from f,
        n: usize,
        ab: [(i64, i64); n],
    }
    let a = ab.iter().map(|x| x.0).collect();
    let b = ab.iter().map(|x| x.1).collect();
    Input { n, a, b }
}

pub fn read<T: Copy + PartialOrd + std::fmt::Display + std::str::FromStr, R: RangeBounds<T>>(
    token: Option<&str>,
    range: R,
) -> Result<T, String> {
    if let Some(v) = token {
        if let Ok(v) = v.parse::<T>() {
            if !range.contains(&v) {
                Err(format!("Out of range: {}", v))
            } else {
                Ok(v)
            }
        } else {
            Err(format!("Parse error: {}", v))
        }
    } else {
        Err("Unexpected EOF".to_owned())
    }
}

#[derive(Hash, PartialEq, Eq, Clone, Copy, PartialOrd, Ord)]
pub struct Pos {
    pub x: i64,
    pub y: i64,
}

pub struct Operation {
    pub from: Pos,
    pub to: Pos,
}

pub struct Output {
    pub out: Vec<Operation>,
}

const MAX: i64 = 1_000_000_000;

pub fn parse_output(input: &Input, f: &str) -> Result<Output, String> {
    let mut tokens = f.split_whitespace();
    let output_max = input.n * 5;
    let m = read(tokens.next(), 0..=output_max)?;
    let mut out = Vec::new();
    for _ in 0..m {
        let from_x = read(tokens.next(), 0..MAX)?;
        let from_y = read(tokens.next(), 0..MAX)?;
        let to_x = read(tokens.next(), 0..MAX)?;
        let to_y = read(tokens.next(), 0..MAX)?;

        let op = Operation {
            from: Pos{x: from_x, y: from_y},
            to: Pos{x: to_x, y: to_y}
        };

        out.push(op);
    }

    Ok(Output { out })
}

fn gen_coordinates(n: usize, rng: &mut rand_chacha::ChaCha20Rng) -> Vec<i64> {
    if n == 0 {
        vec![]
    } else {
        let mut result = vec![0];
        while result.len() < n {
            let x = rng.gen_range(1..MAX);
            if result.iter().all(|&y| y != x) {
                result.push(x);
            }
        }

        result.shuffle(rng);
        result
    }
}

pub fn gen(seed: u64) -> Input {
    let mut rng = rand_chacha::ChaCha20Rng::seed_from_u64(seed);
    let n = 1000;
    let a = gen_coordinates(n, &mut rng);
    let b = gen_coordinates(n, &mut rng);
    Input { n, a, b }
}

pub fn compute_score(input: &Input, out: &Output) -> (i64, String) {
    let (mut score, _, err, _) = compute_score_details(input, &out.out, out.out.len());
    if err.len() > 0 {
        score = 0;
    }
    (score, err)
}

fn compute_cost(from: Pos, to: Pos) -> i64 {
    to.x - from.x + to.y - from.y
}

fn compute_score_details(input: &Input, out: &Vec<Operation>, t: usize)
                             -> (i64, i64, String, HashSet::<Pos>) {
    let mut positions = HashSet::new();
    positions.insert(Pos{x: 0, y: 0});
    let cost = out[..t]
        .iter()
        .map(|Operation{from, to}| compute_cost(*from, *to))
        .sum::<i64>();
    for Operation{from, to} in &out[..t] {
        if positions.contains(from) {
            if to.x >= from.x && to.y >= from.y {
                positions.insert(*to);
            } else {
                let msg = format!("Invalid target: {}, {}, {}, {}",
                                  from.x, from.y, to.x, to.y);
                return (0, cost, msg.to_owned(), positions);
            }
        } else {
            let msg = format!("Invalid source: {}, {}, {}, {}",
                              from.x, from.y, to.x, to.y);
            return (0, cost, msg.to_owned(), positions);
        }
    }

    if t == out.len() {
        for (x, y) in input.a.iter().zip(input.b.iter()) {
            let p = Pos{x: *x, y: *y};
            if !positions.contains(&p) {
                let msg = format!("Missing ({}, {})", x, y);
                return (0, cost, msg.to_owned(), positions);
            }
        }
        let score = calc_score_from_cost(input, cost);
        (score, cost, String::new(), positions)
    } else {
        (0, cost, String::new(), positions)
    }
}

fn calc_score_from_cost(input: &Input, cost: i64) -> i64 {
    let max = input.a.iter().max().unwrap().max(input.b.iter().max().unwrap());
    div_round(input.n as i64 * max * 1_000_000, 1 + cost)
}

fn div_round(x: i64, y: i64) -> i64 {
    assert!(y > 0);
    assert!(x >= 0);
    (x + y / 2) / y
}

pub fn vis_default(input: &Input, out: &Output) -> (i64, String, String) {
    let (mut score, _, err, svg) = vis(input, &out.out, out.out.len());
    if err.len() > 0 {
        score = 0;
    }
    (score, err, svg)
}

pub fn vis(input: &Input, out: &Vec<Operation>, t: usize) -> (i64, i64, String, String) {
    let W = 600;
    let H = 600;
    let amax = input.a.iter().max().unwrap_or(&1).max(&1);
    let bmax = input.b.iter().max().unwrap_or(&1).max(&1);
    let (score, cost, err, positions) = compute_score_details(input, &out, t);
    let mut doc = svg::Document::new()
        .set("id", "vis")
        .set("viewBox", (-5, -5, W + 10, H + 10))
        .set("width", W + 10)
        .set("height", H + 10)
        .set("style", "background-color:white");
    let xscale = *amax as f64 / W as f64;
    let yscale = *bmax as f64 / H as f64;
    let mut points = BTreeMap::new();
    for i in 0..input.n {
        points.insert(Pos{x: input.a[i], y: input.b[i]}, (true, false));
    }
    for p in positions.iter().copied() {
        if let Some(val) = points.get_mut(&p) {
            val.1 = true;
        } else {
            points.insert(p, (false, true));
        }
    }

    let to_xy = |p: Pos| -> (f64, f64) {
        let x = p.x as f64 / xscale;
        let y = (bmax - p.y) as f64 / yscale;
        (x, y)
    };

    for Operation{from, to} in &out[..t] {
        let path = {
            let s = to_xy(*from);
            let g = to_xy(*to);
            let data = svg::node::element::path::Data::new()
                .move_to(s)
                .line_to(g);
            svg::node::element::Path::new()
                .set("stroke", "blue")
                .set("stroke-width", 3)
                .set("stroke-opacity", "0.2")
                .set("d", data)
        };
        doc = doc.add(path);
    }

    for (p, (is_target, is_reached)) in points {
        let color = if is_target && is_reached {
            "red"
        } else if is_target {
            "black"
        } else {
            assert!(is_reached);
            "blue"
        };
        let (x, y) = to_xy(p);
        let target = svg::node::element::Circle::new()
            .set("fill", color)
            .set("cx", x)
            .set("cy", y)
            .set("r", 3);
        let group = svg::node::element::Group::new()
            .add(svg::node::element::Title::new(format!("({}, {})", p.x, p.y)))
            .add(target);
        doc = doc.add(group);
    }

    doc = doc.add(Style::new(format!(
        "text {{text-anchor: middle;dominant-baseline: central;}}"
    )));
    (score, cost, err, doc.to_string())
}
