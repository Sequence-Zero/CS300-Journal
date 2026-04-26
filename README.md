# CS300-Journal
What was the problem you were solving in the projects for this course?

The problem was to design and implement a course planner that could load Computer Science course data, organize it by course number, print the full course list in alphanumeric order, and display individual course information with prerequisites when requested.

How did you approach the problem?

I approached the problem by first analyzing different data structures, including vectors, hash tables, and binary search trees. Since the program needed both efficient searching and an ordered course list, I chose a binary search tree because it naturally supports in-order traversal for sorted output while still allowing efficient course lookup.

How did you overcome any roadblocks you encountered?

I overcame roadblocks by breaking the program into smaller pieces, such as CSV parsing, course insertion, course searching, and menu handling. I also added input validation, uppercase conversion, file-open error handling, and cleanup for line-ending issues so the program could handle user input and file data more reliably.

How has your work on this project expanded your approach to designing software and developing programs?

This project helped me think more carefully about design before writing code. Instead of only focusing on making the program work, I had to compare data structures, evaluate runtime tradeoffs, and choose an implementation that matched the actual requirements of the program.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

This project improved the way I separate responsibilities in my code. Using a Course structure, a BinarySearchTree class, helper functions, and clear menu logic made the program easier to read, test, and update. It also showed me the value of writing code that can be reused or modified without having to rewrite the entire program.
