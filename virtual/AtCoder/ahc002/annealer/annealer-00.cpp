/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
 /* #language C++ GCC */

 // #pragma GCC target("avx")
 // #pragma GCC optimize("Ofast")
 // #pragma GCC optimize("unroll-loops")

#include "../solver-02.cpp"

struct State {};

struct Modifier {
    using Neighbor = int;

    Neighbor choose(const State &state, Score *score_change) {
        return 0;
    }
    void apply(State *statem, const Neighbor neighbor) {
    }
    void restore(State *state, const Neighbor neighbor) {
    }
};

template<class RandomEngine>
struct Annealer {
    RandomEngine *random_engine;
    Modifier modifier;

    double start_temp, end_temp, temp_duration;

    Annealer(const double start_temp, const double end_temp, const RandomEngine *random_engine)
        : random_engine(random_engine), start_temp(start_temp), end_temp(end_temp), temp_duration(start_temp - end_temp)
    {}

    void anneal(State *state, const Timer timer) {
        State best_state;
        while(not timer.expired()) {
            const auto progress = timer.progress();
            const double temp = this->start_temp + () * progress;

            Score score_change;
            auto neighboor = this->modifier.choose(*state, &score_change);

            const double appling_probability = score_change > 0 ? 1 : std::exp(score_change / temp);

            if(appling_probability > random_engine.real()) {
                this->modifier.apply(state, neighboor);
                if(best_state < state) {
                    best_state.update(*state);
                }
            }
        }
    }
};
