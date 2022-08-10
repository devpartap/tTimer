#### This program lacks many things, you can help by adding these features

- [X] save data locally
- this is so that the data of the day is saved locally and we can track productivity through the day.
- [ ] add command feature
- in the second thread which takes care of starting and stopping the time, a `std::cin` to be used so that we can take commands from the user
- [ ] add command to view week and month data from save.txt
- the history view only shows data of the day, a command to enable it for week or month will be helpful
- [ ] making a struct to replace `std::String`
- `std::String` is the return type of two functions in the program but in both of those the return size is known so heep allocation can be prevented. a struct which contains array element to be used as a return type will make program little bit faster.