#pragma once

#include<map>
#include<stack>
#include<cmath>
#include<string>
#include<vector>
#include<memory>
#include<sstream>

#include "function.h"

using std::string; using std::vector;

/**
 * Namespace for handling evaluation.
 */
namespace Evaluation {
    float evaluate_rpn(const string & rpn, const float & x);
    void get_ab(std::stack<float> & stack, float & a, float & b);
    vector<string> tokenize_comm_string(const string & eval_string);
    float assign_rmse(const string & rpn, const vector<float> & samples,
                      const Function & f);

    // Operation constants.
    const string VAR = "x";
    const string ADD = "+";
    const string SUBTRACT = "-";
    const string MULTIPLY = "*";
    const string DIVIDE = "/";

    /**
     * Evaluates the rpn string at x.
     * @param  rpn string, reverse polish notation.
     * @param  x   float
     * @return     float
     */
    float evaluate_rpn(const string & rpn, const float & x) {
        std::stack<float> stack; // Intermediate value stack.

        std::stringstream ss(rpn);
        string current_val;

        float a, b;

        while (getline(ss, current_val, ' ')) {
            if (current_val == VAR) {
                stack.push(x);
            }
            else if (current_val == ADD) {
                get_ab(stack, a, b);
                stack.push(a + b);
            }
            else if (current_val == SUBTRACT) {
                get_ab(stack, a, b);
                stack.push(b - a);
            }
            else if (current_val == MULTIPLY) {
                get_ab(stack, a, b);
                stack.push(b * a);
            }
            else if (current_val == DIVIDE) {
                get_ab(stack, a, b);
                stack.push((a == 0) ? 1 : b / a); // Protected division.
            }
            else {  // A consatnt value (not operator or variable).
                stack.push(stof(current_val));
            }
        }

        return stack.top();
    }

    /**
     * Get two values off a stack.
     * @param stack stack<float> &
     * @param a     float &
     * @param b     float &
     */
    void get_ab(std::stack<float> & stack, float & a, float & b) {
        a = stack.top();
        stack.pop();
        b = stack.top();
        stack.pop();
    }

    /**
     * Tokenizes the string communicated through MPI.
     * @param  eval_string string, comma separated rpn strings.
     * @return             vector<string>
     */
    vector<string> tokenize_comm_string(const string & rpn_string) {
        vector<string> rpn_strings;

        string temp;
        std::stringstream stream(rpn_string);

        while(getline(stream, temp, ',')) {
            rpn_strings.push_back(temp);
        }

        return rpn_strings;
    }

    /**
     * Exaluate a RPN string on a vector of samples in parallel.
     * @param  rpn     string, function in reverse polish notation.
     * @param  samples vector<float>, samples from the domain of a function.
     * @return         float, rmse between samples and predictions.
     */
    float assign_rmse(const string & rpn,
                      const vector<float> & samples,
                      shared_ptr<Function> f) {
        float rmse = 0; // Root mean squared error.

        #pragma omp parallel
        {
            float truth, pred;  // Thread private variables to hold ground truth and prediction.

            #pragma omp for reduction(+:rmse)
            for (int i = 0; i < samples.size(); i++) {
                truth = f->call(samples[i]);
                pred = evaluate_rpn(rpn, samples[i]);
                rmse += (truth - pred) * (truth - pred);
            }
        }

        return sqrt(rmse / samples.size());
    }
}
