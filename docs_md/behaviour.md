\page behaviour Behaviour

Behaviour Guide
---

# Introduction

Behaviour is a group of statistics for every entity in the project that will be collected during runtime by defining a collection of actions and behaviour of entities based on their given specific values (such as what to eat, who to run away from, etc...).

This page will explain in detail the set of rules and how they work to give a better understanding on how to build upon the Behaviour and define future entities.

## The File

You can find the file in 
>ecosystem/src/behaviour

# Organization

You can define a new entity with a new line, following the defined order listed defined in the first line as

> Entity|EatValue|Eats*EatValue|AfraidValue|Afraid*AfraidValue|


    1. Entity
    2. EatValue
    3. Eats*Eatvalue
    4. AfraidValue
    5. Afraid*AfraidValue

An example of this structure would be

1\) `R|2|T|G|1|F|`

or

2\) `F|1|R|0|`


### Entity

The first value of the new line will point to the corresponding entity that will receive the following values. It is represented with a single char, the one equal to the enum table called **Type** in entity.h.

In example 1) would the the `R` as in Rabbit. In example 2) is `F` as in Fox.

### EatsValue

The second value is an indication of how many values the program will read following this, interpreting as a group, in this case is a group of entitiese that this one can eat.

Not that every value with a name ending with Value (EatsValue, AfraidValue, ...) is always an indication of the corresponding group size.

In example 1) would the the `2`. In example 2) is `1`.

\todo The rest... goodnight.

### Separation

Knowing that the program will read each line, needing to separate each value, these will be between a **'|' (pipe character)**

# Info

\b Behaviour

\version 1

\date 04-03-2023
