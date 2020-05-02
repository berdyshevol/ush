# SHELL GRAMMAR
For the bases of our shell grammar the following article is taken:
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
    word-sequence
    parameter-assignment

#### parameter-assignment _(one of):_
    parameter-name=word <whitespaces> simple-command
    parameter-name=word

#### parameter_reference _(one of):_
    $parameter-name
    ${parameter-name}

#### parameter_name _(one of):_
     one of: *  @  #  ? -  $ !
     (_|a-z|A-Z)(_|a-z|A-Z|0-9){1,}

#### word_sequence _(one of):_
    word<whitespaces>word_sequence
    word
    
\* _the first word is a command which can be alias, 
or if it starts with \ it is not alias. Command is either external or builtin command._
#### whitespaces _(one of):_
    whitespace whitespaces
    whitespace

#### whitespace _(one of):_
    one of: <space> <tab> <newline>
    
#### word _(one of):_
    plain_string[word]
    quoted_string[word]
    parameter_reference[word]
    command_substitution[word]
    file_expansion
    redirection_operator

#### plain_string _(one of):_
    series all chars except for whitespace, ", ', `, (, ), {, {
    escape_sequence[plain_string]

#### escape_sequence:
	escape followed by one of: <space>, \, ”, ’,  $,   (,   ),   {,   }, `

#### quoted_string:
	'string'

#### dquoted_string
	"string"

#### string _(one of):_
	plain_string[whitespaces string]
	parameter_reference[string]
	command_substitution[string]

#### command_substitution _(one of):_
    $(list)
    `list`

#### file-expansion _(one of):_
    ~file-path
    ~-file-path
    ~+file-path

#### redirection_operator _(one of):_
	>, 2>
	>>, 2>>
	<
\* _we did not implemented_ `<<`
