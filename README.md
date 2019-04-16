# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Writeup

### PID procedure followed to complete the project
The procedure to complete the project was first, try to optimize the hyperparameters `p`, `d` and `i` from scratch
using the twiddle algorithm implemented in `PID.cpp`. This approach did not work well because the track is so narrow
that it was impossible for the car to recover from outside the road. The next approach was to find a good set of 
hyperparameters by hand. I found that a good set of hyperparameters were `p=0.147988`, `d=3.05349` and `i=0`. 
From that set of hyperparameters I could start to use the twiddle algorithm to tune even more and find a more optimal 
set of values but I found that initializing the twiddle algorithm with large values of `dp` 
(for example with ones like in the lesson) makes the car to go off the road again, so I had to put these values be 
really small, `dp`, `dd` and `di` to `0.0001`.

I then decided to experiment adding another PID controller for the throttle, but at some point the velocity makes 
the car to go off the road, so I decided to not include a controller for this, and keep the throttle value of `0.3`

Then, the final procedure to calculate the steering angle is as follows: based on some parameters `p`, `d` and `i` 
calculated by hand, the program runs the twiddle algorithm to fine tune the parameters and calculate new values for 
`p`, `d` and `i` (`Twiddle` function in `PID.cpp`). Then, based on the current error (cte), the error terms `diff_cte` 
(differential term), `ìnt_cte` (integral term) and `total_cte` (total error) are calculated 
(function `UpdateError` in `PID.cpp`). Finally the steering angle is retrieved in the function `TotalError` in `PID.cpp`. 

### Effect of Proportional (P) component
The Proportional component has the effect of adjust the steering angle based on the error. It is really important because
 otherwise the car would not be aligned with the trajectory.

### Effect of Differential (D) component
The Proportional component is not enough, as the car start oscillating around the trajectory, so it is necessary the D
component to correct this behavior. Specifically  this component measures the difference between previous error 
and the actual error. This component is really important, because when you leave it to zero, the car start
oscillating too much and eventually ends off the road.
 

### Effect of Integral (I) component
The Integral component is important to eliminate systematic bias that is present for example when the tires are not 
perfectly aligned. What this component does, is to have into account the sum of all previous errors. 
In this problem there is no such problem, so I decided to leave this component to zero and the car still drives as expected. 

### Final hyperparameters
The final values of the hyperparameters obtained by tuning with the twiddle algorithm are `p=0.157824`, `d=3.0641`,
 and `i=0.00994305`


---

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

Fellow students have put together a guide to Windows set-up for the project [here](https://s3-us-west-1.amazonaws.com/udacity-selfdrivingcar/files/Kidnapped_Vehicle_Windows_Setup.pdf) if the environment you have set up for the Sensor Fusion projects does not work for this project. There's also an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3).

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

