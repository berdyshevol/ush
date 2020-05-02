# Unix shell in C (MacOs)
Shell in C close to zsh. 

## This shell implements:
1. execution of external commands (bin files) 
2. execution of builtins
3. meta-circular interpreter,
4. interpretation of complex grammar of input line including command separator ( ; ), logic operators ( && || ), pipeline ( | ), command substitution, redirections,
5. expansions of tilda (~),
6. variables ( $name, ${name}),
7. escape working accordingly in no quote, quote, double quote expressions,
8. Ctrl+C, Ctrl+D,
9. command history,
10. backspace key while inputting line.

### 1. Execution external commands (bin files)
Bin files are executed in a separate process.
    _e.g._
    `ls`
    `ls -la`
    `/bin/ls -l`

## 2. Builtins implemented in the shell:
1. Echo
_e.g._ `echo "CBL World"`
    `echo CBL World`
    `echo 'CBL World'`
    `echo -n "\a"`
2. Exit
3. cd
4. pwd
5. env
6. set
7. unset
8. export
9. fg
10. path
11. yes
12. true
13. false
14. jobs
15. which

### 3. Meta-circular interpreter
Parsing and execution of the input line is done by implementation of [meta-circular interpreter](https://en.wikipedia.org/wiki/Meta-circular_evaluator) described in the book _Structure and Interpretation of Computer Programs_.

#### 3.1 Shell Grammar
The shell’s grammar is based on zsh grammar http://zsh.sourceforge.net/Doc/Release/Shell-Grammar.html

#### 3.2 Operator precedence
1. `;`
2. `||`  `&&`
3. `|`
4. `=` `>` `>>` `<` `~`

#### 3.3 Grammar
Details of grammar are [here](/docs/grammar.md)

#### 3.4 Order of expansion performance
The following types of expansions are performed in the indicated order in five steps:

1. Alias Expansion
2. Process Substitution
3. Parameter Expansion (only $name and ${name})
4. Command Substitution
5. Arithmetic Expansion
6. Brace Expansion
7. These five are performed in left-to-right fashion. On each argument, any of the five steps that are needed are performed one after the other. Hence, for example, all the parts of parameter expansion are completed before command substitution is started. After these expansions, all unquoted occurrences of the characters ‘\’,‘’’ and ‘"’ are removed.
8. Filename Expansion


