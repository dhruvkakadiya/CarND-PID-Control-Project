# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Project Summary
I implemented a PID controller in C++ to keep a car stay on track. Thec controller outputs steering angle and throttle value using cross track error, driving angle, and driving speed as input. 

In the following output demod, the car can reach as fast as 30 mph.

![final](./gif/full_lap.gif) 

## PID Controller
* P - Proportional: Control is proportional to error. Variable Kp determines how fast the control response to the error. The bigger the Kp is, the faster the car reaches the reference state. However if Kp is too big, it overshoots and the car drives off track.

When a smaller Kp is used, it takes the car longer to return to the reference track. When the car is turing, it gets very close to the outer lane, since it cannot respond to the CTE fast enough.

![small_kp](./gif/small_kp_v2.gif) 

On the other hand, when Kp is large, there is oscillation due to overshoot.

![large_kp](./gif/large_kp_v2.gif) 

* I - Integral: Integral controller is used when there is systematic bias, Since there isn't any in this case, integral controller isn't used.

* D - Derivative: Control is proportional to the rate of error. The goal of a derviative controller is to bring the rate of error to zero. It serves a damping effect, reducing overshoot. 

When Kd is small, it is under damped - the car still oscillates a lot.

![small_kd](./gif/small_kd.gif) 

Larger Kd delays the controller responding to errors. Captured drive below shows that the car takes longer to start turning when there are curves

![small_kd](./gif/small_kd.gif) 

## Tuning

For this controller I used manual tuning. I first set all PID controller variables to zeros except for Kp. Then I increased Kp until observing that the car drives ok on most roads, except for curvers. Then I increased Kd untill a successful lap is observed.


## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)


