# SHELL GRAMMAR
For the basis of our shell grammar the following article is taken:
[zsh grammar shell](http://zsh.sourceforge.net/Doc/Release/Shell-Grammar.html)

## Grammar

#### list _(one of):_
    sublist ; list
    sublist;
    sublist<newline>
    sublist

#### sublist _(one of):_
    pipeline && sublist
    pipeline || sublist
    pipeline

#### pipeline _(one of):_
    simple-command | pipeline
    simple-command

\* operators `;` `&&` `||` `|` can be surrounded by whitespaces 

#### simple-command _(one of):_
    string
    parameter-assignment

#### parameter-assignment _(one of):_
    parameter-name=word [<whitespaces> simple-command]
    parameter-name="string" [<whitespaces> simple-command]
    parameter-name='string' [<whitespaces> simple-command]

#### parameter-name _(one of):_
     one of: *  @  #  ? -  $ !
     (_|a-z|A-Z)(_|a-z|A-Z|0-9){1,}

#### string _(one of):_
    plain-string[string]
    quoted-string[string]
    double-quoted-string[string]
    parameter-reference[string]
    command-substitution[string]
    file-expansion
    redirection-operator[string]
    
#### plain-string _(one of):_
     word whitespaces plain-string
     word
\* _the first word is a command which can be alias, 
or if it starts with \ it is not alias. Command is either external or builtin command._

#### whitespaces _(one of):_
    whitespace whitespaces
    whitespace

#### whitespace _(one of):_
    one of: <space> <tab> <newline>

#### word _(one of):_
    series all chars except for whitespace, ", ', `, (, ), {, {
    escape_sequence[plain_string]

#### escape_sequence:
	escape followed by one of: <space>, \, ”, ’,  $,   (,   ),   {,   }, `

#### quoted_string:
	'string'

#### double-quoted-string:
	"string"

#### parameter-reference _(one of):_
    $parameter-name
    ${parameter-name}

#### command-substitution _(one of):_
    $(list)
    `list`

#### file-expansion _(one of):_
    ~file-path
    ~-file-path
    ~+file-path

#### redirection_operator _(one of):_
	> file-name
	2> file-name
	>> file-name
	2>> file-name
	< file-name
\* _we did not implemented_ `<<`
