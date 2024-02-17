# Taurus
The Taurus Project is a collection of tools and libraries made for the Taurus Programming Language (TRS) and the Taurus Scripting Language (TRSS). All tools strive to be as independent as my knowledge will allow.

## Fundamentals
<ul>
  <li><b>No syntax sugar</b> - will make the code more readable</li>
  <li><b>No compiler's magic</b> - will allow the programmer to have more control on what is really going on and what the compiler is doing</li>
  <li><b>Uniform syntax</b> - one operator always means the same</li>
  <li><b>Trust</b> - TRS and TRSS are not made for beginners! They can give you good results or headache</li>
</ul>

## Everything is subject to change
I am open to suggestions and objective criticism. This project is created for me and it has to meet my requirements in the first place, but I also create it because I want to learn more, so my approach, assumptions and solutions may change. Any feedback is welcome.

# Libraries
For now only 3 libraries are available. This will change in the future.

## Taurus Argument Parser
TRSAP is something like getopt (or getopt_long) but for Taurus.

## Taurus Command Line Interface
TRSCLI is not complete yet. For now it is logging library only.

## Taurus Regular Expression
TRSRE is a simple (and dumb) library for matching regexps in Taurus, but the main thing is trsre_get_token function written for parsing regexps into tokens. More complete is C++ version trsre::parse_rule. 
### Important! This library is made for Taurus standard only! Expressions like a((abc){3,6})|(b) are not supported.

# Executable programs
No main functionality was added, so only one program is available.

## Taurus Regular Expression Compiler
TRSREC is... regex compiler... in Taurus standard... nothing more... depends on trsre...
