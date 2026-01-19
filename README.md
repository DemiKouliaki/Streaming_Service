This project implements a simplified movie streaming service with user and content management.
Movies are organized into six thematic categories using an array of pointers, where each entry points to a sorted singly linked list of movies.
New releases are temporarily stored in a separate sorted singly linked list before being distributed to the category lists.
Users maintain a watch history implemented as a stack and a suggested movies list implemented as a doubly linked list.
Additionally, users are stored in a singly linked list with a sentinel (dummy) node, ensuring efficient operations and proper time complexity.
