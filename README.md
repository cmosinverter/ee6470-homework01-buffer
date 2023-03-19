## Median and Mean filter
This is the project that implements ee6470 homework 1, (60 pt) Data buffers 

 Usage
1. Clone the file to ./ee6470 folder (Git Bash)
```properties
git clone https://github.com/cmosinverter/ee6470_hw1_buffer.git
```
2. Open Windows Powershell
```properties
docker run -h ubuntu --rm --cap-add SYS_ADMIN -it -v "C:\\Users\\<Your Username>:/home/user" ee6470/ubuntu-ee6470:latest
```
3. Login
```properties
/usr/local/bin/entrypoint.sh
```
4. Move to build directory
```properties
cd ~/ee6470/ee6470_hw1_buffer/build
```
5. Run the program using Cmake
```properties
make run
```