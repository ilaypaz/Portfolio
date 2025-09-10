This skiplist class has been modified to 

• Allow repeated values in the skip list
• Search from the right (add a tail member to the skip list class and implement each level as a doubly
linked list)
• Count the number of values that meet certain criteria in a section of the list. For example, the number
of odd values between x and y (where x and y are values of two nodes in the list marking some range
that you want to search through)
• Save the skip list to a file with level info; load it back up from a file (maintaining saved structure)
• Find all common items between two skip lists; find all unique items between two skip lists
• Merge two skip lists into one
• Rescale a skip list (i.e. change the maximum allowed level index and rebuild – perform the rebuilding
within the same skip list to save on memory)
• Change node structure so that each skip list node has ONE next, ONE previous, ONE up and ONE down
links (instead of vectors of links) – you may need to duplicate nodes when a node is promoted to a
higher level

thank you for your attention to this matter
