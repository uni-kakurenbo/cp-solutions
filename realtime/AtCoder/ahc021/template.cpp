/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */


#include "internal/uncopyable.hpp"
#include "timer.hpp"
#include "random/xorshift.hpp"
#include "random/generator.hpp"

namespace lib {


using cost_type = std::int64_t;

using score_type = std::int64_t;
using rating_type = std::int64_t;

lib::random_engine<lib::xorshift> rng;


struct solution {
    rating_type rating = 0;

    friend inline bool operator<(const solution& a, const solution& b) noexcept {
        return a.rating < b.rating;
    }


    inline std::string to_string() const noexcept {
        return "";
    }


    inline std::string _debug() const noexcept { return this->to_string(); }


    inline std::string dump() const noexcept {
        debug(this->rating);
        debug(*this);
    }

    inline void print() const noexcept {
        std::cout << this->to_string() << std::endl;
    }
};


struct evaluator : internal::uncopyable {
    evaluator() {}

    inline rating_type calc_rating(const solution&) noexcept {}

    inline score_type calc_score(const solution&) noexcept {}
};


struct modifier : internal::uncopyable {
    using neighbor_type = int;

    struct restore_hint {
        neighbor_type neighbor = -1;
        rating_type prev_rating = -1, new_rating = -1;

        inline score_type rating_diff() const noexcept { return this->new_rating - this->prev_rating; }
    };

    solution prev;

    modifier() {}

    inline neighbor_type choose(const solution&, const timer::progress_type) const noexcept {
        return 1;
    }

    inline auto apply(solution *const sol, const neighbor_type) noexcept {
        this->prev = *sol;
        return restore_hint{};
    }

    inline void rollback(solution *const sol, const restore_hint&) const noexcept {
        *sol = std::move(this->prev);
    }
};


struct annealer : internal::uncopyable {
    using temperature_type = double;
    using probability_type = double;

    struct state {
      private:
        solution _current, _best;

      public:
        state(const solution &init) : _current(init), _best(init) {}

        inline solution& current() { return this->_current; }
        inline const solution& best() const { return this->_best; }

        inline void update_best() {
            if(this->_current < this->_best) {
                this->_best = this->_current;
                if constexpr(DEV_ENV) debug(this->_best.score);
            }
        }
    };

    modifier& _modifier;
    double start_temp, end_temp, temp_change;

    annealer(modifier& _modifier, const double start_temp, const double end_temp)
        : _modifier(_modifier), start_temp(start_temp), end_temp(end_temp), temp_change(end_temp - start_temp)
    {}

    temperature_type calc_temp(const timer::progress_type progress) const noexcept {
        return start_temp + (end_temp - start_temp) * progress;
    }

    probability_type calc_probability(const rating_type diff, const temperature_type temp) const noexcept {
        if(diff >= 0) return 1;
        return std::exp(diff / temp);
    }


    void anneal(solution *const sol, const timer &_timer) {
        state _state(*sol);

        int loops = 0;

        while(!_timer.expired()) {
            timer::progress_type progress = _timer.progress();

            const auto neighboor = this->_modifier.choose(_state.current(), progress);

            // const auto tmp = _state.current();

            const auto hint = this->_modifier.apply(&_state.current(), neighboor);


            const score_type rating_diff = hint.rating_diff();
            const probability_type prob = this->calc_probability(rating_diff, progress);


            debug(hint.prev_rating, hint.new_rating, rating_diff, prob);

            if(prob > rng.real()) {
                _state.update_best();
            }
            else {
                this->_modifier.rollback(&_state.current(), hint);

                // assert(state.current().score == tmp.score);
                // assert(state.current().scores == tmp.scores);
                // assert(state.current().edges == tmp.edges);
            }

            ++loops;
        }

        debug(loops);

        *sol = std::move(_state.best());
    }
};


} // namespace lib


signed main() {
    return 0;
}
