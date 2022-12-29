#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include <mutex>
#include <thread>

// #define NDEBUG
#undef NDEBUG
#include <cassert>

using namespace std;
using uc = unsigned char;
using us = unsigned short;
using ull = unsigned long long;
using ll = long long;
using pii = pair<int, int>;
using pdi = pair<double, int>;
#define len(c) (int) (c.size())
#define rep(i, from, until) for (int i = (from); i < (until); i++)
#define repr(i, from, until) for (int i = (until) -1; i >= (from); i--)
#define rep0(i, until) rep(i, 0, until)
#define rep0r(i, until) repr(i, 0, until)
#define clamp(a, minimum, maximum) min(max(a, (minimum)), (maximum))

#ifdef _MSC_VER
#include <intrin.h>
#define popcount32(a) ((int) __popcnt(a))
#define popcount64(a) ((int) __popcnt64(a))
#define clz32(a) ((int) __lzcnt(a))
#define clz64(a) ((int) __lzcnt64(a))
inline int ctz32(int a) {
	int i;
	_BitScanForward((unsigned long*) &i, a);
	return i;
}
inline int ctz64(ull a) {
	int i;
	_BitScanForward64((unsigned long*) &i, a);
	return i;
}
#else
#define popcount32(a) ((int) __builtin_popcount(a))
#define popcount64(a) ((int) __builtin_popcountll(a))
#define clz32(a) ((int) __builtin_clz(a))
#define clz64(a) ((int) __builtin_clzll(a))
#define ctz32(a) ((int) __builtin_ctz(a))
#define ctz64(a) ((int) __builtin_ctzll(a))
#endif

class Rnd {
public:
	Rnd() : y(135272729) {
	}

	int getSeed() {
		return y;
	}

	void seed(int y) {
		this->y = y;
	}

	int next() {
		y = y ^ (y << 13);
		y = y ^ (y >> 17);
		return (y = y ^ (y << 5)) & 0x7fffffff;
	}

	int nextInt() {
		return next();
	}

	int nextInt(int n) {
		return next() % n;
	}

	int nextInt(int min, int max) {
		return min + nextInt(max - min + 1);
	}

	double nextFloat() {
		return (double) next() / 0x80000000;
	}

	double nextFloat(double min, double max) {
		return min + nextFloat() * (max - min);
	}

private:
	int y;
};

// return in ms
int timer(bool reset = false) {
	static auto st = chrono::system_clock::now();
	if (reset) {
		st = chrono::system_clock::now();
		return 0;
	} else {
		auto en = chrono::system_clock::now();
		int elapsedTotal = (int) chrono::duration_cast<chrono::milliseconds>(en - st).count();
		return elapsedTotal;
	}
}

bool debug = true;

void tracen() {
}

template <class Head, class... Tail>
void tracen(Head&& head, Tail&&... tail) {
	if (!debug)
		return;
	cerr << head;
	tracen(forward<Tail>(tail)...);
}

template <class... Tail>
void trace(Tail&&... tail) {
	if (!debug)
		return;
	tracen(forward<Tail>(tail)...);
	cerr << endl;
}

template <class Iter>
void tracein(Iter from, Iter until) {
	if (!debug)
		return;
	bool first = true;
	while (from != until) {
		if (first) {
			first = false;
		} else {
			cerr << ", ";
		}
		cerr << *from;
		from++;
	}
}

template <class Iter>
void tracei(Iter from, Iter until) {
	if (!debug)
		return;
	tracein(from, until);
	cerr << endl;
}

void sleepUntil(int until) {
	volatile unsigned int a = 0;
	while (timer() < until)
		a++;
}

void segv() {
	volatile int* a = nullptr;
	*a = 0;
}

void waitForever() {
	while (true)
		getchar();
}

bool writeText(string fileName, string text, bool append = false) {
	ofstream fout;
	fout.open(fileName, append ? ios::out | ios::app : ios::out);
	if (!fout) {
		return false;
	}
	fout << text;
	fout.close();
	return true;
}

pair<string, bool> readText(string fileName) {
	ifstream fin;
	fin.open(fileName, ios::in);
	if (!fin) {
		return make_pair("", false);
	}
	string res;
	string line;
	while (getline(fin, line)) {
		res += line;
		res += "\n";
	}
	return make_pair(res, true);
}

namespace svg {
	using namespace std;

	string s(double x) {
		if (x == (int) x)
			return to_string((int) x);
		string s = to_string(x);
		if (s.find('.') != string::npos) {
			while (s.back() == '0')
				s.pop_back();
		}
		return s;
	}

	string rgb(double r, double g, double b) {
		return "rgb(" + s(lround(r * 255)) + "," + s(lround(g * 255)) + "," + s(lround(b * 255)) + ")";
	}

	string p(string name, double val) {
		return name + "=\"" + s(val) + "\" ";
	}

	string p(string name, string val) {
		return name + "=\"" + val + "\" ";
	}

	string tag(string name, string props) {
		return "<" + name + " " + props + "/>";
	}

	string tag(string name, string props, string content) {
		return "<" + name + " " + props + ">" + content + "</" + name + ">";
	}

	class Style {
	public:
		double sr, sg, sb, sa;               // stroke
		double fr, fg, fb, fa;               // fill
		double e00, e01, e02, e10, e11, e12; // affine matrix
		int textAlign;
		double fs;
		double sw;
		string tf;

		Style()
		    : sr(0), sg(0), sb(0), sa(1), fr(1), fg(1), fb(1), fa(1), e00(1), e01(0), e02(0), e10(0), e11(1), e12(0), textAlign(0), fs(16),
		      sw(1), tf() {
		}

		string stroke() const {
			return sa <= 0 ? "" : p("stroke", rgb(sr, sg, sb)) + p("stroke-opacity", sa) + p("stroke-width", sw);
		}

		string fill() const {
			return fa <= 0 ? p("fill", "none") : p("fill", rgb(fr, fg, fb)) + p("fill-opacity", fa);
		}

		string textAnchor() const {
			return p("text-anchor", textAlign < 0 ? "left" : textAlign > 0 ? "right" : "middle");
		}

		string transform() const {
			return tf.empty() ? "" : p("transform", tf);
		}

		string font() const {
			return p("font-size", fs);
		}
	};

	class Graphics {
	public:
		double screenW;
		double screenH;
		string data;

		Graphics() : screenW(100), screenH(100) {
		}

		void screen(double width, double height) {
			screenW = width;
			screenH = height;
		}

		void clear() {
			data = "";
			st = Style();
		}

		void save() {
			stack.push_back(st);
		}

		void restore() {
			st = stack.back();
			stack.pop_back();
		}

		void stroke(double r, double g, double b, double a = 1) {
			st.sr = r;
			st.sg = g;
			st.sb = b;
			st.sa = a;
		}

		void noStroke() {
			stroke(0, 0, 0, 0);
		}

		void strokeWidth(double w) {
			st.sw = w;
		}

		void fontSize(double size) {
			st.fs = size;
		}

		void fill(double r, double g, double b, double a = 1) {
			st.fr = r;
			st.fg = g;
			st.fb = b;
			st.fa = a;
		}

		void noFill() {
			fill(0, 0, 0, 0);
		}

		void translate(double tx, double ty) {
			st.tf = "translate(" + s(tx) + " " + s(ty) + ")" + st.tf;
		}

		void rotate(double rad, double x = 0, double y = 0) {
			st.tf = "rotate(" + s(rad) + " " + s(x) + " " + s(y) + ")" + st.tf;
		}

		void scale(double sx, double sy) {
			st.tf = "scale(" + s(sx) + " " + s(sy) + ")" + st.tf;
		}

		void line(double x1, double y1, double x2, double y2) {
			data += tag("line", p("x1", x1) + p("y1", y1) + p("x2", x2) + p("y2", y2) + st.stroke() + st.transform()) + "\n";
		}

		void rect(double x, double y, double w, double h) {
			data += tag("rect", p("x", x) + p("y", y) + p("width", w) + p("height", h) + st.stroke() + st.fill() + st.transform()) + "\n";
		}

		void circle(double x, double y, double r) {
			data += tag("circle", p("cx", x) + p("cy", y) + p("r", r) + st.stroke() + st.fill() + st.transform()) + "\n";
		}

		void text(string str, double x, double y) {
			data += tag("text", st.textAnchor() + p("x", x) + p("y", y) + st.font() + st.fill() + st.transform(), str) + "\n";
		}

		string dumpSvg(string id = "", string style = "") const {
			string res;
			res += "<svg ";
			if (id != "")
				res += p("id", id);
			if (style != "")
				res += p("style", style);
			res += p("viewBox", "-1 -1 " + s(screenW + 2) + " " + s(screenH + 2)) + p("xmlns", "http://www.w3.org/2000/svg");
			res += ">\n" + data + "</svg>";
			return res;
		}

	private:
		Style st;
		vector<Style> stack;
	};

	class Movie {
	public:
		vector<string> svgs;

		Movie() {
		}

		void clear() {
			svgs.clear();
		}

		void addFrame(const Graphics& g) {
			svgs.push_back(g.dumpSvg("f" + to_string(svgs.size()), "display:none;pointer-events:none;user-select:none;"));
		}

		string dumpHtml() {
			ostringstream oss;
			int num = (int) svgs.size();
			oss << "<html><body><div id=\"text\">loading...</div>" << endl;
			oss << "<div style=\"display:flex;\"><input type=\"button\" value=\"prev\" style=\"height:32px;\" id=\"prev\"><input "
			       "type=\"button\" value=\"&#x25b6;\" style=\"width:60px;height:32px;\" id=\"play\"><input type=\"button\" value=\"next\" "
			       "style=\"height:32px;margin-right:4px;\" id=\"next\"><label>slow<input type=\"range\" min=\"2\" max=\"60\" step=\"1\" "
			       "value=\"10\" id=\"fps\">fast</label></div>"
			    << endl;
			oss << "<input type=\"range\" min=\"1\" max=\"" << num << "\" step=\"1\" id=\"bar\" style=\"width:500px\"></div>" << endl;
			for (int i = 0; i < num; i++) {
				string& svg = svgs[i];
				oss << svg << endl;
			}

			oss << "<script>\nlet numFrames = " << num << ";";
			oss << R"(
				let text = document.getElementById("text");
				let toggle = document.getElementById("play");
				let bar = document.getElementById("bar");
				let fps = document.getElementById("fps");
				let frames = [];
				for (let i = 0; i < numFrames; i++) {
					let f = document.getElementById("f" + i);
					frames.push(f);
					f.style.display = "none";
				}
				let currentFrame = 0;
				let playing = false;
				let id = 0;
				function play() {
					if (playing) return;
					if (currentFrame == numFrames - 1) setFrame(0);
					playing = true;
					toggle.value = "\u25a0";
					id++;
					setTimeout(() => frame(id), 1000 / fps.value);
				}
				function stop() {
					if (!playing) return;
					id++;
					playing = false;
					toggle.value = "\u25b6";
				}
				toggle.onclick = () => {
					if (playing) stop();
					else play();
				}
				bar.oninput = () => {
					if (currentFrame != bar.value - 1) setFrame(bar.value - 1);
				}
				document.getElementById("prev").onclick = () => { stop(); currentFrame > 0 && setFrame(currentFrame - 1); }
				document.getElementById("next").onclick = () => { stop(); nextFrame(); }
				function setFrame(at) {
					frames[currentFrame].style.display = "none";
					frames[at].style.display = null;
					text.innerText = (at + 1) + " / " + numFrames;
					bar.value = at + 1;
					currentFrame = at;
				}
				function nextFrame() {
					if (currentFrame == numFrames - 1) return;
					setFrame(currentFrame + 1);
					if (currentFrame == numFrames - 1) stop();
				}
				function frame(i) {
					if (i != id) return;
					nextFrame();
					setTimeout(() => frame(i), 1000 / fps.value);
				}
				play();
			)";
			oss << "</script></body></html>" << endl;
			return oss.str();
		}
	};
} // namespace svg

using Graphics = svg::Graphics;
using Movie = svg::Movie;

Movie mov;
Graphics g;

void writeMovie(Movie& mov, string fileName) {
	writeText(fileName, mov.dumpHtml());
}

struct SolverResult {
	int score = 0;
};

constexpr int N = 50;
constexpr double R = 1e9;
constexpr double R2 = 1e9 - 1e5;
constexpr double D = 1e6;
constexpr double TWO_PI = 6.283185307179586;

double distance(double dx, double dy) {
	return sqrt(dx * dx + dy * dy);
}
double distance2(double dx, double dy) {
	return dx * dx + dy * dy;
}

class Server {
private:
public:
	double poss[50][2] = {};
	double qs[1000][4] = {};
	bool found[50] = {};
	int numFound = 0;
	int numQs = 0;
	double sigma = 0;
	Rnd rnd;

	Server() {
	}

	void generate(int seed = 0, int sigmaLevel = -1) {
		if (seed != 0)
			rnd.seed(seed);
		rep0(i, 100) rnd.next();
		numFound = 0;
		numQs = 0;
		sigma = (sigmaLevel == -1 ? rnd.nextInt(1, 100) : 1 + sigmaLevel * 20 + rnd.nextInt(20)) * 0.001;
		rep0(i, 50) {
			while (true) {
				double x = rnd.nextFloat(-1e9, 1e9);
				double y = rnd.nextFloat(-1e9, 1e9);
				if (x * x + y * y > 1e18)
					continue;
				bool ng = false;
				rep0(j, i) {
					if (distance2(poss[j][0] - x, poss[j][1] - y) <= 4 * D * D) {
						ng = true;
						break;
					}
				}
				if (ng)
					continue;
				poss[i][0] = x;
				poss[i][1] = y;
				break;
			}
		}
		// trace("generated. sigma: ", sigma);
	}

	void initialInput(ostream& os) {
		os << sigma << endl;
		// rep0(i, 50) {
		// 	os << (int) poss[i][0] << " " << (int) poss[i][1] << endl;
		// }
	}

	void query(istream& is, ostream& os, double rGuess) {
		double x, y;
		is >> x >> y;
		qs[numQs][0] = x;
		qs[numQs][1] = y;
		qs[numQs][2] = rGuess;
		assert(x * x + y * y <= R * R);

		vector<pdi> weights;
		double wsum = 0;
		rep0(i, 50) {
			if (found[i])
				continue;
			double dist = distance(x - poss[i][0], y - poss[i][1]);
			if (dist <= D) {
				os << (numFound == 49 ? 2 : 1) << " " << (int) poss[i][0] << " " << (int) poss[i][1] << endl;

				found[i] = true;
				numFound++;

				qs[numQs][3] = -1;
				numQs++;

				return;
			}
			double weight = 1 / (dist * dist + 1e-9);
			wsum += weight;
			weights.emplace_back(weight, i);
		}
		double pick = rnd.nextFloat() * wsum;
		int picked = -1;
		for (auto wi : weights) {
			pick -= wi.first;
			picked = wi.second;
			if (pick <= 0)
				break;
		}
		assert(picked != -1);
		double gx = poss[picked][0];
		double gy = poss[picked][1];
		double ang = atan2(gy - y, gx - x);
		double error = sqrt(-2 * log(rnd.nextFloat())) * cos(TWO_PI * rnd.nextFloat()) * sigma;
		ang += error;
		ang = fmod(fmod(ang, TWO_PI) + TWO_PI, TWO_PI);
		os << 0 << " " << ang << endl;

		qs[numQs][3] = ang;
		numQs++;
	}

	void draw(Graphics& g, double r) {
		g.fill(0.9, 0.9, 0.9);
		g.circle(r, r, r);
		double scale = r / R;
		double e = 0.01 * r;
		rep0(i, 50) {
			if (found[i]) {
				g.stroke(1, 0, 0);
			} else {
				g.stroke(0, 0, 0);
			}
			double x = r + poss[i][0] * scale;
			double y = r - poss[i][1] * scale;
			g.line(x - e, y - e, x + e, y + e);
			g.line(x - e, y + e, x + e, y - e);
		}
		rep0(i, numQs) {
			double x = r + qs[i][0] * scale;
			double y = r - qs[i][1] * scale;
			double rGuess = qs[i][2] * scale;
			double res = qs[i][3];
			if (res == -1) {
				g.noStroke();
				g.fill(1, 0.3, 0);
				g.circle(x, y, e * 0.8);
			} else if (numQs - i < 20) {
				g.noStroke();
				bool last = i == numQs - 1;
				g.fill(last, 0, !last);
				g.circle(x, y, e * 0.8);
				if (last) {
					g.noFill();
					g.stroke(1, 0, 1);
					g.circle(x, y, rGuess);
				}
				g.stroke(last, 0, !last);
				g.line(x, y, x + e * 2 * cos(res), y - e * 2 * sin(res));
			}
		}
	}
};

class Candidate {
private:
public:
	double x;
	double y;
	double r;

	Candidate(double x = 0, double y = 0, double r = 0) : x(x), y(y), r(r) {
	}

	bool operator<(const Candidate& c) const {
		return r > c.r;
	}
};

class Refinement {
public:
	double alpha = 0.5;
	double beta = 2.0;
	double gamma = 0.2;
	int step = 0;
	double r = 0;
	double x1 = 0;
	double y1 = 0;
	double x2 = 0;
	double y2 = 0;
	double nx1 = 0;
	double ny1 = 0;
	double nx2 = 0;
	double ny2 = 0;
	int result = 0;
	double rx = 0;
	double ry = 0;

	Refinement() {
	}

	void reset() {
		step = 0;
	}

	void setBase(const Candidate& cand) {
		assert(step == 0);
		step++;
		x1 = cand.x;
		y1 = cand.y;
		r = cand.r;
	}

	void setFirstDirection(double ang) {
		assert(step == 1);
		step++;
		nx1 = cos(ang);
		ny1 = sin(ang);
		computeSecondPos();
	}

	void setSecondDirection(double ang) {
		assert(step == 2);
		step++;
		nx2 = cos(ang);
		ny2 = sin(ang);
		decide();
	}

private:
	void decide() {
		double det = ny1 * nx2 - nx1 * ny2;
		if (abs(det) < 1e-6) {
			result = -1;
			// trace("parallel");
			return;
		}
		double t1 = (-nx2 * y1 + nx2 * y2 + ny2 * x1 - ny2 * x2) / det;
		double t2 = (-nx1 * y1 + nx1 * y2 + ny1 * x1 - ny1 * x2) / det;
		if (abs(t1) > beta * r) {
			if (nx1 * nx2 + ny1 * ny2 > 0) {
				result = -1;
				// trace("failed");
			} else {
				result = 1;
				// trace("another found");
			}
		} else {
			if (t1 > -gamma * r && t2 > 0) {
				result = 0;
				rx = x1 + t1 * nx1;
				ry = y1 + t1 * ny1;
				// trace("refined");
			} else {
				result = 1;
				// trace("another found");
			}
		}
	}

	void computeSecondPos() {
		double tx = -ny1;
		double ty = nx1;
		double cx = x1 + r * nx1;
		double cy = y1 + r * ny1;
		double ax = cx + alpha * r * tx;
		double ay = cy + alpha * r * ty;
		double bx = cx - alpha * r * tx;
		double by = cy - alpha * r * ty;
		double al = distance(ax, ay);
		double bl = distance(bx, by);
		double ae = max(0.0, al - R);
		double be = max(0.0, bl - R);
		if (ae < be) {
			x2 = ax;
			y2 = ay;
			if (ae > 0) {
				x2 /= al;
				y2 /= al;
			}
		} else {
			x2 = bx;
			y2 = by;
			if (be > 0) {
				x2 /= bl;
				y2 /= bl;
			}
		}
	}
};

#define bound(x, y)                          \
	if (x * x + y * y > R2 * R2) {           \
		double s = R2 / sqrt(x * x + y * y); \
		x *= s;                              \
		y *= s;                              \
	}

class Solver {
public:
	int n = -1;
	int m = -1;
	int seed = -1;
	int numCaught = 0;
	Rnd rnd;
	SolverResult res;
	bool isLocal = false;
	double rGuess = 0;
	double sigma = 0;
	double initialSize = 0.1;
	double additionalSize = 0.3;
	double shrinkSize = 0.1;
	double cutoff = 0.1;
	double anotherStep = 1.0;

	Refinement ref;
	priority_queue<Candidate> cands;
	string msg;

	Solver() {
	}

	void load(istream& in) {
		in >> sigma;
		setParams();
		// trace("sigma: ", sigma);
	}

	void load(int seed) {
		this->seed = seed;
		string data = readText("in/"s + (seed < 10 ? "000" : seed < 100 ? "00" : seed < 1000 ? "0" : "") + to_string(seed) + ".txt").first;
		istringstream in(data);
		isLocal = true;
		load(in);
	}

	void solve() {
		res.score = 0;
		numCaught = 0;
	}

	void next(ostream& os) {
		double x, y;
		// trace("next " + ref.step);
		assert(ref.step == 0 || ref.step == 2);
		if (ref.step == 0) {
			ref.setBase(popCand());
			x = ref.x1;
			y = ref.y1;
			rGuess = ref.r;
		} else if (ref.step == 2) {
			x = ref.x2;
			y = ref.y2;
			rGuess = ref.r;
		}
		os << (ll) x << " " << (ll) y << endl;
	}

	bool response(istream& is) {
		// trace("response " + ref.step);
		int type;
		is >> type;
		if (type == 0) {
			double ang;
			is >> ang;

			assert(ref.step == 1 || ref.step == 2);
			if (ref.step == 1) {
				ref.setFirstDirection(ang);
				msg = "first dir decided";
			} else {
				ref.setSecondDirection(ang);

				if (ref.result == -1) {
					// failure
					double r = computeInitialR();
					double x = ref.x1 + r * ref.nx1;
					double y = ref.y1 + r * ref.ny1;
					bound(x, y);
					cands.emplace(x, y, r);
					msg = "failed";
				} else if (ref.result == 0) {
					// successful
					double r = shrinkR(ref.r);
					if (r < cutoff * D) {
						msg = "failed2";
					} else {
						double x = ref.rx;
						double y = ref.ry;
						bound(x, y);
						cands.emplace(x, y, r);
						msg = "refined " + to_string((int) ref.r) + " -> " + to_string((int) r);
					}
				} else {
					assert(ref.result == 1);
					double x = ref.x2 + ref.r * ref.nx2;
					double y = ref.y2 + ref.r * ref.ny2;
					double r = computeInitialR();
					bound(x, y);
					cands.emplace(x, y, r * anotherStep); // add another
					msg = "another one found";
				}

				ref.reset();
			}

			return false;
		} else if (type == 1) {
			msg = "found!";
			numCaught++;
			double x, y;
			is >> x >> y;
			ref.reset();
			return false;
		} else {
			msg = "finished";
			assert(type == 2);
			return true;
		}
	}

private:
	void setParams() {
		initialSize = 0.1;
		additionalSize = 0.2;
		shrinkSize = 0.15 + 0.5 * sigma;
		cutoff = 0.08 + 0.2 * sigma;
		anotherStep = 1.0;
		ref.alpha = 0.3 + 2 * sigma;
		ref.beta = 5.5 - 15 * sigma;
		ref.gamma = 0.3;
		int kind = (int) (sigma * 30 - 0.01);
		switch (kind) {
		case 0:
			rnd.seed(234); // best: 234
			break;
		case 1:
			rnd.seed(234); // best: 234
			break;
		case 2:
			rnd.seed(235); // best: 234
			break;
		}
	}

	double shrinkR(double r) {
		return shrinkSize * r;
	}

	double computeInitialR() {
		return numCaught == 49 ? R * 0.5 : initialSize * R + additionalSize * R * pow(numCaught / 49.0, 3);
	}

	Candidate popCand() {
		if (cands.empty())
			return generateRandomCand();
		auto res = cands.top();
		cands.pop();
		return res;
	}

	Candidate generateRandomCand() {
		double x, y;
		do {
			x = rnd.nextFloat(-1e9, 1e9);
			y = rnd.nextFloat(-1e9, 1e9);
		} while (distance(x, y) > R2);
		return Candidate(x, y, computeInitialR());
	}
};

double tryParam(double initialSize, double additionalSize, double shrinkSize, double cutoff, double anotherStep, double alpha, double beta,
    double gamma, int sigmaLevel) {
	int scoreSum = 0;
	rep0(iter, 500) {
		Server ser;
		Solver sol;
		ser.generate(iter + 100, sigmaLevel);
		{
			ostringstream os;
			ser.initialInput(os);
			istringstream is(os.str());
			sol.load(is);
		}
		sol.initialSize = initialSize;
		sol.additionalSize = additionalSize;
		sol.shrinkSize = shrinkSize;
		sol.cutoff = cutoff;
		sol.anotherStep = anotherStep;
		sol.ref.alpha = alpha;
		sol.ref.beta = beta;
		sol.ref.gamma = gamma;
		int count = 0;
		rep0(t, 1000) {
			ostringstream os;
			sol.next(os);
			count++;
			istringstream is(os.str());
			ostringstream os2;
			ser.query(is, os2, sol.rGuess);
			istringstream is2(os2.str());
			bool end = sol.response(is2);
			if (end)
				break;
		}
		int score = ser.numFound == 50 ? 10000 - 5 * count : 100 * ser.numFound;
		scoreSum += score;
	}
	trace(initialSize, " ", additionalSize, " ", shrinkSize, " ", cutoff, " ", anotherStep, " ", alpha, " ", beta, " ", gamma, " ",
	    sigmaLevel, " ", scoreSum);
	return scoreSum / 500.0;
}

int main() {
#if 1
	Solver sol;
	sol.load(cin);
	while (true) {
		sol.next(cout);
		if (sol.response(cin))
			break;
	}
#elif 0
	rep0(sigmaLevel, 5) {
		trace("for sigma level ", sigmaLevel);
		double sigma = (sigmaLevel * 20 + 10) * 0.001;
		double initialSize = 0.1;
		double additionalSize = 0.2;
		double shrinkSize = 0.15 + 0.5 * sigma;
		double cutoff = 0.08 + 0.2 * sigma;
		double alpha = 0.3 + 2 * sigma;
		double beta = 5.5 - 15 * sigma;
		double gamma = 0.3;
		tryParam(initialSize, additionalSize, shrinkSize, cutoff, 0.8, alpha, beta, gamma, sigmaLevel);
		tryParam(initialSize, additionalSize, shrinkSize, cutoff, 0.9, alpha, beta, gamma, sigmaLevel);
		tryParam(initialSize, additionalSize, shrinkSize, cutoff, 1.0, alpha, beta, gamma, sigmaLevel);
		tryParam(initialSize, additionalSize, shrinkSize, cutoff, 1.1, alpha, beta, gamma, sigmaLevel);
		tryParam(initialSize, additionalSize, shrinkSize, cutoff, 1.2, alpha, beta, gamma, sigmaLevel);
	}
#elif 1
	bool render = true;
	constexpr int QUERY_LIMIT = 1000;

	rep0(iter, 10) {
		int seed = iter + 100;

		Server ser;
		Solver sol;
		ser.generate(seed);

		{
			ostringstream os;
			ser.initialInput(os);
			istringstream is(os.str());
			sol.load(is);
		}

		if (render) {
			mov.clear();
			g.screen(500, 550);
		}

		rep0(t, QUERY_LIMIT) {
			ostringstream os;
			sol.next(os);
			istringstream is(os.str());
			ostringstream os2;
			ser.query(is, os2, sol.rGuess);
			istringstream is2(os2.str());
			bool end = sol.response(is2);
			if (render) {
				g.clear();
				ser.draw(g, 250);
				g.fontSize(12);
				g.fill(0, 0, 0);
				g.text(sol.msg, 250, 515);
				g.text("sigma is " + to_string(ser.sigma), 250, 535);
				mov.addFrame(g);
			}
			if (end)
				break;
		}
		writeMovie(mov, "movie_" + to_string(seed) + ".html");
	}
#elif 1
	int num = 50;
	int from = 0;
	int stride = 1;
	int single = 0;

	int seeds[1000] = {};
	int times[1000] = {};
	int scores[1000] = {};

	int scoreSum = 0;

	vector<int> seedList = {19, 8, 14, 26, 43};
	bool useList = false;

	if (useList && !seedList.empty()) {
		useList = true;
		num = len(seedList);
		single = -1;
	}

	rep0(t, num) {
		timer(true);
		int seed = useList ? seedList[t] : single != -1 ? single : from + t * stride;
		trace("\n------------ SOLVING SEED ", seed, " ------------");
		Solver s;
		s.load(seed);
		s.solve();
		if (single == -1)
			trace("score: ", s.res.score);
		scoreSum += s.res.score;
		seeds[t] = seed;
		scores[t] = s.res.score;
		times[t] = timer();
		if (single != -1)
			break;
	}
	if (single == -1) {
		trace("--- summary ---");
		pii timesRank[1000] = {};
		pii scoresRank[1000] = {};
		rep0(t, num) {
			timesRank[t] = pii(times[t], t);
			scoresRank[t] = pii(scores[t], t);
		}
		sort(timesRank, timesRank + num);
		sort(scoresRank, scoresRank + num);
		trace("time:");
		rep0r(t, num) {
			int i = timesRank[t].second;
			int s = seeds[i];
			string space = s < 10 ? "   " : s < 100 ? "  " : s < 1000 ? " " : "";
			trace("  seed ", space, s, ": ", times[i], " ms (score ", scores[i], ")");
		}
		trace("score:");
		rep0r(t, num) {
			int i = scoresRank[t].second;
			int s = seeds[i];
			string space = s < 10 ? "   " : s < 100 ? "  " : s < 1000 ? " " : "";
			trace("  seed ", space, s, ": ", scores[i], " (time ", times[i], " ms)");
		}
		trace("seed:");
		rep0r(i, num) {
			int s = seeds[i];
			string space = s < 10 ? "   " : s < 100 ? "  " : s < 1000 ? " " : "";
			trace("  seed ", space, s, ": ", scores[i], " (time ", times[i], " ms)");
		}
		trace("total score: ", scoreSum, ", mean: ", (int) (scoreSum / (double) num * 100) / 100.0);
	} else {
		trace("total score: ", scoreSum, " time = ", timer());
	}

#elif 1
	timer(true);
	Solver s;
	s.init(cin);
	s.solve();
#elif 1
#endif
	return 0;
}
