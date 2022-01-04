# Let's Chat

**Let's Chat** is a communication protocol for text chats inspired over **HTTP** and **IRC**.

Born as a school experiment, **Let's Chat** points to have a standard communication between the server and client.

In addition to **protcol documentation**, you can find a **C++ API** library.

***

## Request

The **request** message must have the following structure.

`<COMMAND> <username>@<channel> [<HEADERS>] <MESSAGE>`

The **COMMAND** is the name of the command the client send to the server. The aviable commands are:
- **CONNECT**
- **DISCONNECT**
- **SEND**
- **BROADCAST**

Then there is the **name** of the **command sender** and the **name** of the **channel** where we need to execute the command, separated by a **@** symbol.

Between the brackets ("**[]**") we have the message **headers list**. The headers list is a **list** of a **key**-**value** pair.

Each header **entry** (each pair) must be **separated** by a **semicolon** ("**;**").
The **key** and the **value** of an header entry must be separated by a **colon** ("**:**") both.

In both cases there can be **withespaces**, or not.

Lastly there is the **MESSAGE**, a string.

An example is provided below
```http
SEND danieleguglietti@general [created_at:1637262323026;] Hi everyone!
```

***

## Response

The **response** message must have the following structure.

`<CODE> [<HEADERS>] <MESSAGE>`

The **CODE** is a **positive integer number** from **200** to **299** for **success** codes and from **400** to **499** for **error** codes.
The code rappresents the **status** of the response. It says if all gone **right** or **wrong**.
There are **some code numbers** wich are **reserved** by default:
  - 200 => **CONNECTED** - A connection has been established successfully.
  - 201 => **DISCONNECTED** - The client has been disconnected successfully.
  - 202 => **FORWARDED** - A message has been forwarded to the channel/user or when a messages has been broadcasted.
  - 203 => **RECEIVING** - A message has been received.
  - 400 => **DROPPED** - The connection has been dropped.
  - 401 => **UNKOWN COMMAND** - A command hasn't been recognized by the server..
  - 402 => **BLOCKED** - A message couldn't been forwarded.

The **headers list** is the same as the **request** one, but it's sent by the server.

The **MESSAGE** is a string. If the server is **forwading** a message from a channel, the **MESSAGE** is the one sent by the sender.

An example is provvided below
```http
202 [author:danieleguglietti;channel:general;] Hi everyone!
```

***

## Constraints

Each fields has constraints:
 - Command Field
   - Only characters allowed
 - Code Field
   - Only integer numbers allowed
   - The code number should match the range (200-299 or 400-499)
 - Username Field
   - Only characters, number and underscore allowed
   - Maximum length of the username is 16 characters.
 - Channel Field
   - Maximum length of the channel name is 32 characters.
 - Headers Field
   - The headers field can contain a maximum of 32 header entries
   - Maximum length of the entry key and value is 32 characters
 - Message Field
   - The massage can contain every type of character, escape characters included.
   - Maximum length of the message is 1024 characters.

***

## Future Rules and Implementation

Here is a list of the future rule I would define or some of the future implementation:
 - Asymmetric Encryption of messages
