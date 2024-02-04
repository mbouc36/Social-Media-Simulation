# Social Media Simulation
### Description
This project is a social media simulation implemented in C. It loads user data from a CSV file containing usernames, passwords, friends, and posts. Each row in the CSV represents a new user. The simulation allows for user interaction through a menu-driven interface with features such as logging in, creating a new user, adding posts, adding friends, and viewing posts from all users or specific friends.

### Features
- Load User Data: Reads a CSV file to load users' data.
- Authentication: Allows users to log in using their username and password.
- User Management: Users can create a new account or exit the application.
- Social Interactions:
  - Display individual posts.
  - Display a list of friends.
  - Add new posts.
  - Add new friends.
  - Display posts from all users.
- Menu-Driven Interface: Easy navigation through options for a smooth user experience.
### Getting Started
#### Prerequisites
GCC compiler or any C language compiler installed on your system.
#### Installation
1. Clone the repository to your local machine:
```
git clone <repository-URL>
```
2. Navigate to the project directory:
```
cd social-media-simulation
```
3. Compile the project using GCC:
```
gcc -o socialMediaSimulation main.c
```
#### Usage
To run the simulation, execute the compiled program:
```
./socialMediaSimulation
```
Follow the on-screen instructions to navigate through the application.

### Contributing
Contributions are welcome! Please feel free to submit pull requests or open issues to improve the functionality or documentation.

### License
This project is licensed under the GNU General Public License v3.0 - see the LICENSE file for details.

### Acknowledgments
This project is a simulation and does not connect to real social media services.
Designed as an educational tool to understand the basics of file handling and user authentication in C.
