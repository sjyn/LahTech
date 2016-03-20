breed [humans human]
breed [zombies zombie]
breed [spatters spatter]

globals [food t4courage t4speed t4mutation]
patches-own [heat shells countdown]

turtles-own [hunger sense speed courage mutation fitness heredity ammo]


;;---------------------
;;first round processes
;;---------------------

to setup
  ca
  set t4courage initial-survivor-courage
  set t4speed initial-survivor-speed
  set t4mutation initial-mutation-deviation
  set-default-shape spatters "fspatter"
  setpatches
  makehumans
  makezombies
  foodcount
  reset-ticks
end


to go
  ask humans [
    set hunger hunger - 1
    set fitness fitness + 1
    death
    humantarget
    eat-food
    kill-zombie
  ]
  diffuse heat (heat-evap-rate / 100)
  ask zombies [
    set hunger hunger - 1
    z-death
    zombietarget
    lurch
    eat-brains
  ]
  ask patches [
    grow-food
    set heat heat * (100 - heat-evap-rate) / 100

    ]
  if show-heat? [
    ask patches [
      set pcolor scale-color green heat 0.1 5
    ]
  ]
  foodcount
  tick
;;  if (count humans < progenitors)
;;    [setup-round-end]
  ;;if (count humans = 0)
    ;;[setup-round-end]
  ;;if (count zombies = 0)
    ;;[setup-round-end]
end


to setup-round-end
  set t4courage progenitor-courage
  set t4speed progenitor-speed
  set t4mutation progenitor-mutation
  clear-turtles
  clear-links
  setpatches
  makehumans
  makezombies
  foodcount
  reset-ticks
  set-current-plot "populations"
    clear-plot
end

;;---------------------
;;environment processes
;;---------------------

;;the default graveyard is black earth, piles of food & ammo are
;;colored 13 red, assuming that heat vision isn't on. regardless of
;;what color they are, they carry the owned value of having
;;shells = 2
to setpatches
  clear-patches
  clear-drawing
  ask patches [set pcolor black]
  ask patches [
    if (abs random-normal 0 1 > 2.5)
      [set pcolor 13
       set shells 2]
    ]
end


;;countdown acts as a ticker that keeps track of when the food &
;;ammo here will respawn
to grow-food
  if shells = 1 [
    ifelse countdown <= 0
      [ set pcolor 13
        set shells 2
        set countdown food-respawn-time ]
      [ set countdown countdown - 1 ]
 ]
end

;;this is a reporter for the interface that keeps track of how many
;;piles of food and ammo are currently active
to foodcount
  set food count patches with [shells = 2]
end


;;----------------
;;human processes
;;----------------

;;make a number of humans equal to the integer set on the survivor
;;slider. heredity is used for finding the "original humans" amongst
;;all the spattered zombie corpses at the end of the round
to makehumans
  set-default-shape humans "fhuman"
  create-humans survivors
  [
    set size 2
    set hunger 100
    set fitness 1
    set speed (t4speed * mutation-variation)
    set courage (t4courage * mutation-variation)
    set mutation (t4mutation * mutation-variation)
    set heredity 1
    set ammo 0
    setxy random-xcor random-ycor
  ]
end


;;hunger - closest-food = time to starvation
to humantarget
  ifelse (closest-zombie * courage) >= closest-food
    [run-for-food
     scamper]
    [run-from-zombies
     fd speed
     set heat heat + 100]
end


;;points the human at a patch with food and ammo on it
to run-for-food
  face min-one-of patches with [shells = 2] [distance myself]
end


;;points exactly away from the nearest zombie
to run-from-zombies
  face min-one-of zombies [distance myself]
  rt 180
end


;;reports the distance to the nearest zombie
to-report closest-zombie
  ifelse (count zombies > 0)
    [report distance min-one-of zombies [distance myself]]
    [report 1000]
end


;;reports the distance to the nearest patch with food & ammo
to-report closest-food
  ifelse (count patches with [shells = 2] > 0)
    [report distance min-one-of patches with [shells = 2] [distance myself]]
    [report 1000]
end


;;when heading for food, running forward by the raw amount of speed
;;could overshoot the patch with food on it. this corrects for that
;;potential error
to scamper
  ifelse (closest-food < speed)
    [fd closest-food]
    [fd speed]
  set heat heat + 100
end

;;pick up some food and ammo and recolor the patch dark grey
;;to show that it is spent until grow-food regenerates it
to eat-food
  if (shells = 2)
   [ask patch-here [set pcolor 1]
    ask patch-here [set shells 1]
    set hunger hunger + 30
    set ammo ammo + 1
  ]
end

;;if there are zombies on this square and you have shells, shoot.
;;this kills the zombie.
to kill-zombie
  let prey one-of zombies-here
  if (prey != nobody)
    [if (ammo >= 1) [
       ask prey [set hunger 0]
       set hunger hunger + 10
       set ammo 0]
     ]
end

;;when humans die, they turn into freshly minted zombies
;;heredity carries the fact that they began the round as
;;a human, which means their courage and speed are weighed
;;at the end of the round, based on their (also carried)
;;fitness ranking
to death
  if hunger <= 0 [
     let p fitness
     let q heredity
     set breed zombies
     set fitness p
     set heredity q
     set size 2
     set hunger 100]
end


;;----------------
;;zombie processes
;;----------------


;; create the starting zombies
to makezombies
  set-default-shape zombies "fzombie"
  create-zombies shamblers
  [
    set size 2
    set hunger 100
    set fitness 0
    set speed shambler-speed
    set courage 0
    set heredity 0
    set ammo 0
    setxy random-xcor random-ycor
  ]
end


;;move zombies forward how ever much the shambler-speed slider allows
to lurch
  fd shambler-speed
end


;; decision tree for zombies path selection
;; need some exception handling for when there's no humans
to zombietarget
  ifelse (count humans > 0)
    [let nearest-human min-one-of humans [distance myself]
     let dist-nearest-human distance nearest-human
     ifelse (dist-nearest-human < 3)
      [i-see-brains]
      [look-for-brains]
    ]
    [look-for-brains]
end


;; if there's a human in sight range, go for the human
to i-see-brains
  face min-one-of humans [distance myself]
end


;; if there's no human in sight range, look for heat signature.
;; if no heat, just like... spin around and hope for the best
to look-for-brains
  ifelse (heat >= 0.05)
    [seek-brains]
    [rt random 360]
end


;; senses heat in a 90 degree window in front of the zombie
;; points the zombie in the hottest direction in that window
to seek-brains
  let scent-ahead human-scent   0
  let scent-right human-scent  45
  let scent-left  human-scent -45
  if (scent-right > scent-ahead) or (scent-left > scent-ahead)
  [ ifelse scent-right > scent-left
    [ rt 45 ]
    [ lt 45 ]]
end


;; reports scent of human in whatever direction
to-report human-scent [angle]
  let p patch-right-and-ahead angle 1
  if (p = nobody)
    [report 0]
  report [heat] of p
end

;; EAT BRAINS!!! (pretty self explainatory)
;;doesn't automatically kill the human subject
;;does add to the predator's health
to eat-brains
  let prey one-of humans-here
  if (prey != nobody)
    [ask prey [set hunger hunger - 20]
     set hunger hunger + 10
     ]
end


;;when zombies die, they turn into spatters
;;order of operations is important here, so that
;;heredity and fitness scores are carried on to the now
;;"completely dead" corpse
to z-death
  if hunger <= 0 [
     let p fitness
     let q heredity
     set breed spatters
     set fitness p
     set heredity q
     set size 2
     set hunger 10000]
end

;;-------------------------------
;;observer and reporter processes
;;-------------------------------

;;gives the average courage for the n (progenitors) longest surviving humans
to-report progenitor-courage
  report mean [courage] of (max-n-of progenitors turtles with [heredity = 1] [fitness])
end


;;gives the average speed for the n (progenitors) longest surviving humans
to-report progenitor-speed
  report mean [speed] of (max-n-of progenitors turtles with [heredity = 1] [fitness])
end


;;gives the average mutation rate for the n (progenitors) longest surviving humans
to-report progenitor-mutation
  report mean [mutation] of (max-n-of progenitors turtles with [heredity = 1] [fitness])
end

;;used for mutating all the traits, including the standard deviation used to mutate
to-report mutation-variation
  report 1 + (random-normal 0 t4mutation)
end
@#$#@#$#@
GRAPHICS-WINDOW
391
10
950
590
30
30
9.0
1
14
1
1
1
0
1
1
1
-30
30
-30
30
1
1
1
ticks
30.0

SLIDER
10
74
184
107
survivors
survivors
1
20
19
1
1
NIL
HORIZONTAL

SLIDER
10
111
184
144
shamblers
shamblers
1
200
42
1
1
NIL
HORIZONTAL

BUTTON
10
10
79
43
setup
setup
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
92
10
159
43
go
go
T
1
T
OBSERVER
NIL
NIL
NIL
NIL
0

PLOT
985
335
1301
532
populations
time
pop.
0.0
100.0
0.0
100.0
true
true
"" ""
PENS
"humans" 1.0 0 -13345367 true "" "plot count humans"
"zombies" 1.0 0 -2674135 true "" "plot count zombies"
"food" 1.0 0 -10899396 true "" "plot food"

MONITOR
1017
539
1088
584
zombies
count zombies
3
1
11

MONITOR
1092
539
1174
584
humans
count humans
3
1
11

MONITOR
1178
539
1254
584
NIL
food
0
1
11

SLIDER
193
112
365
145
heat-evap-rate
heat-evap-rate
0
99
25
1
1
NIL
HORIZONTAL

SWITCH
193
74
350
107
show-heat?
show-heat?
0
1
-1000

SLIDER
9
173
181
206
food-respawn-time
food-respawn-time
45
180
180
1
1
NIL
HORIZONTAL

SLIDER
10
235
182
268
shambler-speed
shambler-speed
0.5
1.5
0.75
0.05
1
NIL
HORIZONTAL

TEXTBOX
13
56
163
74
Populations:
11
0.0
1

TEXTBOX
197
56
347
74
Heat signatures:
11
0.0
1

TEXTBOX
15
156
165
174
Supplies:
11
0.0
1

SLIDER
190
275
362
308
initial-survivor-speed
initial-survivor-speed
0
2
1
0.1
1
NIL
HORIZONTAL

TEXTBOX
13
219
163
237
Population attributes:
11
0.0
1

SLIDER
10
275
187
308
initial-survivor-courage
initial-survivor-courage
0.1
3
1
0.1
1
NIL
HORIZONTAL

MONITOR
960
220
1035
265
Avg Courage
mean [courage] of turtles with [heredity = 1]
17
1
11

MONITOR
1040
220
1105
265
Avg Speed
mean [speed] of turtles with [heredity = 1]
17
1
11

TEXTBOX
10
335
160
353
Genetic constraints:
11
0.0
1

SLIDER
10
350
182
383
progenitors
progenitors
0
10
2
1
1
NIL
HORIZONTAL

SLIDER
190
235
392
268
initial-mutation-deviation
initial-mutation-deviation
0
0.1
0.04
0.005
1
NIL
HORIZONTAL

PLOT
960
10
1390
210
average-traits
trait
time
0.0
1.0
-2.0
3.0
true
true
"" ""
PENS
"courage" 1.0 0 -14439633 true "" "plot mean [courage] of turtles with [heredity = 1]"
"speed" 1.0 0 -13345367 true "" "plot mean [speed] of turtles with [heredity = 1]"
"mutation (x10)" 1.0 0 -7500403 true "" "plot mean [mutation] of turtles with [heredity = 1] * 10"

MONITOR
1110
220
1197
265
Avg Mutation
mean [mutation] of turtles with [heredity = 1]
17
1
11

@#$#@#$#@
## THE "ZOMBIES EAT EVERYBODY" MODEL

I built this model to have a little bit of fun with the idea of two competing, mutually competitive predators. Zombies are intended to remain a constant challenge to the human population, the environment randomized according to a set of fairly tightly constrained criteria. Humans have some hope of killing a straggling zombie or two, but will likely spend most of their time running and scavenging.

Over time, the humans are free to breed and mutate into the most survivable possible agents. Survivability is judged for this model on the number of ticks human agents are able to persist in each round. Genetic traits which influence survivability are 'courage' - the propensity to risk being bitten in order to get food & ammo, and 'speed' - the rate at which humans are allowed to run from the shambling horde.


## THE SYSTEMS SCIENCY BITS

This model uses a genetic algorithm to seek improving performance of a subordinate (badly outnumbered) predator through generational optimum seeking. Humans start off with a predeterimined sense of courage (risk taking for food) and a preset ability to run at a speed proportional to their zombie competitors.

The most long-lived of each successive generation (determined by survival duration) is interbred, with some variable chance for mutation, into what the author hopes will be ever more survivable generations.

Speed has no upper bound, and courage is allowed to turn into cowardice (negative courage) as merit for either trait demonstrates.


## RULES OF ZOMBIE ETTIQUETTE

Zombies are hungry, and will eventually starve if they don't manage to eat some tasty humans.

Zombies hunt humans using two independent senses. Each tick, zombies look for humans using their relatively short-ranged (3 blocks) eyes. If they see a human, they'll follow the closest one. If their eyes fail them, zombies sniff the air for human heat signatures. If they spot a heat signature, they'll follow it as best they're able until they're able to lock eyes on their prey.

Zombies will nibble at their human prey each turn until they wind down the human's hunger value, converting them to a zombie who will then join the hunt for human brains.

Once zombies starve to death or are killed, they turn into a spatter that retains the record of any human survival characteristics to be used for the next round.


## RULES FOR HUMANS

Humans are both hungry and scared, and will have to make choices every round as to whether or not they're willing to risk running for food while zombies are nearby. The balance of this choice is made on a trait called "courage", but the success of this choice can be significantly altered by a given human's speed. Humans also have a third trait called 'mutation'. The intent of this mutatable constraint on mutation is to find an evolutionary "sweet-spot" where the right amount of variation genetically evolves along with the genetic traits that mutation governs.

Humans have some ability to defend themselves against individual zombies, but a herd is likely to kill them quickly. For each pile of food they find, they also pick up a single shotgun shell. Humans are all assumed to have a shotgun ready, and to be dead shots at close range.

Each the end of each round, a set of progenitors will be chosen from those who managed to remain human longest, and their traits will be averaged into the baseline for the population of the next round.


## RULES FOR THE ENVIRONMENT

Each round the environment will spawn a number of food and ammo piles. Placement of these piles is random, and the number of piles is somewhat random as well (each patch makes a roll against a normal distribution, and the patch becomes food if the roll is more than 2.5 standard deviations from the mean).


## HOW TO USE THIS MODEL

The broad intention of this model is to gain some insight into the value of courage under duress. While the configurability of the model allows for a number of


## INTERESTING THINGS TO NOTICE

Pay specific attention to the emerging benefit of the two mutatable traits (courage/cowardice and speed). Going in, I really had no expectation for whether courage would be beneficial. My assumption was that no amount of speed gain is bad, but I figured I would likely clarify this over time.

What is particularly disheartening is that there comes a point when the challenge surrounding each human is so great that their best recourse for prolonged survival is complete cowardice. This also seems to atrophy the speed trait, leaving our humans effectively legless lumps, waiting to die. They starve quickly if they aren't eaten, but they still live longer than they would if they took any risk at all. :(


## THINGS TO TRY

What changes in very cold environments? (turn heat evap rate way up)

What happens to courage when speed is held static and cannot evolve? What

What happens to the benefit of courage when humans outnumber zombies (predation is eased)?

What happens to the stability of the model when mutation is rampant? When mutation is
tightly constrained?


## LOG OF TIME SPENT

~20 hours writing & rewriting code
~12 hours researching code, scouring other models for example code
@#$#@#$#@
default
true
0
Polygon -7500403 true true 150 5 40 250 150 205 260 250

airplane
true
0
Polygon -7500403 true true 150 0 135 15 120 60 120 105 15 165 15 195 120 180 135 240 105 270 120 285 150 270 180 285 210 270 165 240 180 180 285 195 285 165 180 105 180 60 165 15

arrow
true
0
Polygon -7500403 true true 150 0 0 150 105 150 105 293 195 293 195 150 300 150

box
false
0
Polygon -7500403 true true 150 285 285 225 285 75 150 135
Polygon -7500403 true true 150 135 15 75 150 15 285 75
Polygon -7500403 true true 15 75 15 225 150 285 150 135
Line -16777216 false 150 285 150 135
Line -16777216 false 150 135 15 75
Line -16777216 false 150 135 285 75

bug
true
0
Circle -7500403 true true 96 182 108
Circle -7500403 true true 110 127 80
Circle -7500403 true true 110 75 80
Line -7500403 true 150 100 80 30
Line -7500403 true 150 100 220 30

butterfly
true
0
Polygon -7500403 true true 150 165 209 199 225 225 225 255 195 270 165 255 150 240
Polygon -7500403 true true 150 165 89 198 75 225 75 255 105 270 135 255 150 240
Polygon -7500403 true true 139 148 100 105 55 90 25 90 10 105 10 135 25 180 40 195 85 194 139 163
Polygon -7500403 true true 162 150 200 105 245 90 275 90 290 105 290 135 275 180 260 195 215 195 162 165
Polygon -16777216 true false 150 255 135 225 120 150 135 120 150 105 165 120 180 150 165 225
Circle -16777216 true false 135 90 30
Line -16777216 false 150 105 195 60
Line -16777216 false 150 105 105 60

car
false
0
Polygon -7500403 true true 300 180 279 164 261 144 240 135 226 132 213 106 203 84 185 63 159 50 135 50 75 60 0 150 0 165 0 225 300 225 300 180
Circle -16777216 true false 180 180 90
Circle -16777216 true false 30 180 90
Polygon -16777216 true false 162 80 132 78 134 135 209 135 194 105 189 96 180 89
Circle -7500403 true true 47 195 58
Circle -7500403 true true 195 195 58

circle
false
0
Circle -7500403 true true 0 0 300

circle 2
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240

cow
false
0
Polygon -7500403 true true 200 193 197 249 179 249 177 196 166 187 140 189 93 191 78 179 72 211 49 209 48 181 37 149 25 120 25 89 45 72 103 84 179 75 198 76 252 64 272 81 293 103 285 121 255 121 242 118 224 167
Polygon -7500403 true true 73 210 86 251 62 249 48 208
Polygon -7500403 true true 25 114 16 195 9 204 23 213 25 200 39 123

cylinder
false
0
Circle -7500403 true true 0 0 300

dot
false
0
Circle -7500403 true true 90 90 120

face happy
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 255 90 239 62 213 47 191 67 179 90 203 109 218 150 225 192 218 210 203 227 181 251 194 236 217 212 240

face neutral
false
0
Circle -7500403 true true 8 7 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Rectangle -16777216 true false 60 195 240 225

face sad
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 168 90 184 62 210 47 232 67 244 90 220 109 205 150 198 192 205 210 220 227 242 251 229 236 206 212 183

fhuman
false
0
Circle -2064490 true false 110 5 80
Rectangle -2064490 true false 127 79 172 94
Polygon -2064490 true false 195 90 240 150 225 180 165 105
Polygon -2064490 true false 105 90 60 150 75 180 135 105
Polygon -13345367 true false 105 90 120 195 90 285 105 300 135 300 150 225 165 300 195 300 210 285 180 195 195 90

finfected
false
10
Circle -10899396 true false 110 5 80
Rectangle -10899396 true false 127 79 172 94
Polygon -13840069 true false 195 90 240 150 225 180 165 105
Polygon -13840069 true false 105 90 60 150 75 180 135 105
Polygon -2674135 true false 105 90 120 195 90 285 105 300 135 300 150 225 165 300 195 300 210 285 180 195 195 90

fish
false
0
Polygon -1 true false 44 131 21 87 15 86 0 120 15 150 0 180 13 214 20 212 45 166
Polygon -1 true false 135 195 119 235 95 218 76 210 46 204 60 165
Polygon -1 true false 75 45 83 77 71 103 86 114 166 78 135 60
Polygon -7500403 true true 30 136 151 77 226 81 280 119 292 146 292 160 287 170 270 195 195 210 151 212 30 166
Circle -16777216 true false 215 106 30

flag
false
0
Rectangle -7500403 true true 60 15 75 300
Polygon -7500403 true true 90 150 270 90 90 30
Line -7500403 true 75 135 90 135
Line -7500403 true 75 45 90 45

flower
false
0
Polygon -10899396 true false 135 120 165 165 180 210 180 240 150 300 165 300 195 240 195 195 165 135
Circle -7500403 true true 85 132 38
Circle -7500403 true true 130 147 38
Circle -7500403 true true 192 85 38
Circle -7500403 true true 85 40 38
Circle -7500403 true true 177 40 38
Circle -7500403 true true 177 132 38
Circle -7500403 true true 70 85 38
Circle -7500403 true true 130 25 38
Circle -7500403 true true 96 51 108
Circle -16777216 true false 113 68 74
Polygon -10899396 true false 189 233 219 188 249 173 279 188 234 218
Polygon -10899396 true false 180 255 150 210 105 210 75 240 135 240

fspatter
true
0
Polygon -2674135 true false 120 150 105 135 45 180 120 150 90 210 135 165 120 150 150 150 135 120 120 150
Polygon -2674135 true false 135 165 150 240 165 165 135 165 180 150 150 150 135 165
Polygon -2674135 true false 166 164 216 210 179 152 168 164

fzombie
false
10
Circle -7500403 true false 110 5 80
Rectangle -7500403 true false 127 79 172 94
Polygon -7500403 true false 195 90 240 150 225 180 165 105
Polygon -7500403 true false 105 90 60 150 75 180 135 105
Polygon -6459832 true false 105 90 120 195 90 285 105 300 135 300 150 225 165 300 195 300 210 285 180 195 195 90

house
false
0
Rectangle -7500403 true true 45 120 255 285
Rectangle -16777216 true false 120 210 180 285
Polygon -7500403 true true 15 120 150 15 285 120
Line -16777216 false 30 120 270 120

leaf
false
0
Polygon -7500403 true true 150 210 135 195 120 210 60 210 30 195 60 180 60 165 15 135 30 120 15 105 40 104 45 90 60 90 90 105 105 120 120 120 105 60 120 60 135 30 150 15 165 30 180 60 195 60 180 120 195 120 210 105 240 90 255 90 263 104 285 105 270 120 285 135 240 165 240 180 270 195 240 210 180 210 165 195
Polygon -7500403 true true 135 195 135 240 120 255 105 255 105 285 135 285 165 240 165 195

line
true
0
Line -7500403 true 150 0 150 300

line half
true
0
Line -7500403 true 150 0 150 150

pentagon
false
0
Polygon -7500403 true true 150 15 15 120 60 285 240 285 285 120

plant
false
0
Rectangle -7500403 true true 135 90 165 300
Polygon -7500403 true true 135 255 90 210 45 195 75 255 135 285
Polygon -7500403 true true 165 255 210 210 255 195 225 255 165 285
Polygon -7500403 true true 135 180 90 135 45 120 75 180 135 210
Polygon -7500403 true true 165 180 165 210 225 180 255 120 210 135
Polygon -7500403 true true 135 105 90 60 45 45 75 105 135 135
Polygon -7500403 true true 165 105 165 135 225 105 255 45 210 60
Polygon -7500403 true true 135 90 120 45 150 15 180 45 165 90

sheep
false
15
Circle -1 true true 203 65 88
Circle -1 true true 70 65 162
Circle -1 true true 150 105 120
Polygon -7500403 true false 218 120 240 165 255 165 278 120
Circle -7500403 true false 214 72 67
Rectangle -1 true true 164 223 179 298
Polygon -1 true true 45 285 30 285 30 240 15 195 45 210
Circle -1 true true 3 83 150
Rectangle -1 true true 65 221 80 296
Polygon -1 true true 195 285 210 285 210 240 240 210 195 210
Polygon -7500403 true false 276 85 285 105 302 99 294 83
Polygon -7500403 true false 219 85 210 105 193 99 201 83

square
false
0
Rectangle -7500403 true true 30 30 270 270

square 2
false
0
Rectangle -7500403 true true 30 30 270 270
Rectangle -16777216 true false 60 60 240 240

star
false
0
Polygon -7500403 true true 151 1 185 108 298 108 207 175 242 282 151 216 59 282 94 175 3 108 116 108

target
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240
Circle -7500403 true true 60 60 180
Circle -16777216 true false 90 90 120
Circle -7500403 true true 120 120 60

tree
false
0
Circle -7500403 true true 118 3 94
Rectangle -6459832 true false 120 195 180 300
Circle -7500403 true true 65 21 108
Circle -7500403 true true 116 41 127
Circle -7500403 true true 45 90 120
Circle -7500403 true true 104 74 152

triangle
false
0
Polygon -7500403 true true 150 30 15 255 285 255

triangle 2
false
0
Polygon -7500403 true true 150 30 15 255 285 255
Polygon -16777216 true false 151 99 225 223 75 224

truck
false
0
Rectangle -7500403 true true 4 45 195 187
Polygon -7500403 true true 296 193 296 150 259 134 244 104 208 104 207 194
Rectangle -1 true false 195 60 195 105
Polygon -16777216 true false 238 112 252 141 219 141 218 112
Circle -16777216 true false 234 174 42
Rectangle -7500403 true true 181 185 214 194
Circle -16777216 true false 144 174 42
Circle -16777216 true false 24 174 42
Circle -7500403 false true 24 174 42
Circle -7500403 false true 144 174 42
Circle -7500403 false true 234 174 42

turtle
true
0
Polygon -10899396 true false 215 204 240 233 246 254 228 266 215 252 193 210
Polygon -10899396 true false 195 90 225 75 245 75 260 89 269 108 261 124 240 105 225 105 210 105
Polygon -10899396 true false 105 90 75 75 55 75 40 89 31 108 39 124 60 105 75 105 90 105
Polygon -10899396 true false 132 85 134 64 107 51 108 17 150 2 192 18 192 52 169 65 172 87
Polygon -10899396 true false 85 204 60 233 54 254 72 266 85 252 107 210
Polygon -7500403 true true 119 75 179 75 209 101 224 135 220 225 175 261 128 261 81 224 74 135 88 99

wheel
false
0
Circle -7500403 true true 3 3 294
Circle -16777216 true false 30 30 240
Line -7500403 true 150 285 150 15
Line -7500403 true 15 150 285 150
Circle -7500403 true true 120 120 60
Line -7500403 true 216 40 79 269
Line -7500403 true 40 84 269 221
Line -7500403 true 40 216 269 79
Line -7500403 true 84 40 221 269

wolf
false
0
Polygon -16777216 true false 253 133 245 131 245 133
Polygon -7500403 true true 2 194 13 197 30 191 38 193 38 205 20 226 20 257 27 265 38 266 40 260 31 253 31 230 60 206 68 198 75 209 66 228 65 243 82 261 84 268 100 267 103 261 77 239 79 231 100 207 98 196 119 201 143 202 160 195 166 210 172 213 173 238 167 251 160 248 154 265 169 264 178 247 186 240 198 260 200 271 217 271 219 262 207 258 195 230 192 198 210 184 227 164 242 144 259 145 284 151 277 141 293 140 299 134 297 127 273 119 270 105
Polygon -7500403 true true -1 195 14 180 36 166 40 153 53 140 82 131 134 133 159 126 188 115 227 108 236 102 238 98 268 86 269 92 281 87 269 103 269 113

x
false
0
Polygon -7500403 true true 270 75 225 30 30 225 75 270
Polygon -7500403 true true 30 75 75 30 270 225 225 270

@#$#@#$#@
NetLogo 5.3
@#$#@#$#@
setup
set grass? true
repeat 75 [ go ]
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
default
0.0
-0.2 0 0.0 1.0
0.0 1 1.0 0.0
0.2 0 0.0 1.0
link direction
true
0
Line -7500403 true 150 150 90 180
Line -7500403 true 150 150 210 180

@#$#@#$#@
1
@#$#@#$#@
