# [STL]Break words

# Break words

# Description
<p>Given a dictionary of words, and then a sentence, break the sentence in to words separated by blank spaces.<br />
If more than one words in the dictionary matches the input, use the longest word. As in the example below, if both &quot;student&quot; and &quot;students&quot; match, we will use &quot;students&quot;, the longer word.<br />
If no word in the dictionary matches, output each single character as a word. As in the example below, &quot;sysu&quot; is output as &quot;s y s u&quot;.</p>

# Input
<p>An integer N representing the number of words in the dictionary.<br />
N lines, each of which is a words in the dictionary.<br />
A final line containing the sentence to be broken into words.<br />
The dictionary contains less than 1000 words.<br />
The words in the dictionary contains less than 10000 characters in total.<br />
The sentence contains less than 1000 characters.</p>

# Output
<p>&nbsp;A line with its words separated by one blank space. There is no blank after the last word.</p>

# Sample_Input
```
6
the
they
student
students
are
area
theyaresysustudents
```

# Sample_Ouput
```
they are s y s u students
```

# Hint


