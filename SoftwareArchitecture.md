Firstly, we use the layered architecture<sup>1</sup> because of it allows to separate details of interaction with hardware from implementation of the game.
Secondly, we choose object-oriented paradigm and a C++ as programming language, therefore we require additional layer to delimit with low-level vendor's C-libraries.
As result we have the architecture which consists of three layers, as shown on figure 1.

![http://neek-klondike.googlecode.com/svn/wiki/sw-architecture.png](http://neek-klondike.googlecode.com/svn/wiki/sw-architecture.png)

Figure 1 - Layered architecture of NEEK Klondike

Application layer contains only domain-specific logic.
But this logic requires access to some hardware features, like displaying information on the LCD or processing touch-screen's events.
Communication with hardware it is another layer of abstraction, so it represented as the independent integration layer.
Last layer is the libraries from the hardware vendor.

It should be noted that integration layer uses C-libraries but provides object-oriented interface.
Consequently, this layer changes paradigm from structural to object-oriented.

  1. Frank Buschmann, Regine Meunier, Hans Rohnert, Peter Sommerlad, and Michael Stal. _Pattern-Oriented Software Architecture Volume 1: A System of Patterns._ Wiley, 1 edition, August 1996