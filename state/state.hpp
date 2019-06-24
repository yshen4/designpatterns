#ifndef YAAL_STATE_H
#define YAAL_STATE_H

#include <string>
#include <iostream>

namespace yaal {
    class CircuitBreaker;

    class State {
    public:
        enum eState{
            open,
            closed,
            halfopen
        };

    protected:
        const eState state;
        CircuitBreaker *context;

    public:
        State(eState s, CircuitBreaker *ctx)
        :   state(s),
            context(ctx)
        { }

        virtual eState get_state() { return state; }

        // abstract function
        virtual void handle() = 0;
        virtual void transit() = 0;
        virtual std::string get_name() = 0;
    };

    static State *create_state(State::eState state, CircuitBreaker *ctx);

    class CircuitBreaker {
    private:
         // configurations
         State *closed_state, *open_state, *halfopen_state;
         int timeout, failure_threshold, retry_period;

         // runtime states
         State *cur_state;
         int lastfailtime, failure_count;

    public:
         CircuitBreaker(int time_out = 5, int failure_thr = 3, int retry_t = 15)
         :   timeout(time_out),
             failure_threshold(failure_thr),
             retry_period(retry_t)
         {
             closed_state = create_state(State::closed, this);
             open_state = create_state(State::open, this);
             halfopen_state = create_state(State::halfopen, this);
             cur_state = closed_state;
         }

         void set_state(State::eState st) {
             switch(st) {
             case State::open:
                 cur_state = open_state;
                 break;
             case State::halfopen:
                 cur_state = halfopen_state;
                 break;
             case State::closed:
             default:
                 cur_state = halfopen_state;
                 break;
             }
         }

         void call() {
             cur_state->handle();
         }

         bool retry() {
             timeout++;
             if (failure_count < failure_threshold) {
                 time_t now = time(nullptr);
                 int diff_time = now - lastfailtime;
                 if (diff_time > retry_period)
                     return true;
             }
             
             return false;
         }

         void record_failure() {
             ++failure_count;
             lastfailtime = time(nullptr);
         }
    };

    class Open:public State {
    public:
        Open(CircuitBreaker *ctx)
        :   State(State::open, ctx)
        { }

        virtual void handle() {
            // if open, transit to half-open
            std::cout << "State: " << get_name() << std::endl;
        }

        virtual void transit() {
            if (context->retry()) 
               context->set_state(State::halfopen);
        }

        virtual std::string get_name() { return "open"; }
    };

    class Closed:public State {
    public:
        Closed(CircuitBreaker *ctx)
        :   State(State::closed, ctx)
        { }

        virtual void handle() {
            // if closed 
            std::cout << "State: " << get_name() << std::endl;
        }

        virtual void transit() {
        }

        virtual std::string get_name() { return "closed"; }
    };

    class Halfopen:public State {
    public:
        Halfopen(CircuitBreaker *ctx)
        :   State(State::halfopen, ctx)
        { }

        virtual void handle() {
            // if halfopen 
            std::cout << "State: " << get_name() << std::endl;
            
        }

        virtual void transit() {
        }

        virtual std::string get_name() { return "halfopen"; }
    };

    State *create_state(State::eState state, CircuitBreaker *ctx) {
        State *rt = nullptr;
        switch(state) {
        case State::open:
             rt = new Open(ctx);
             break;
        case State::halfopen:
             rt = new Halfopen(ctx);
             break;
        case State::closed:
        default:
             rt = new Closed(ctx);
             break;
        }
        return rt;
    }
}

#endif
