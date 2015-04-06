

# Introduction #

According to [architecture](Architecture.md) we have two packages: KLONDIKE and NEEK, which are shown on figure 1.
NEEK package corresponds to integration layer and KLONDIKE package corresponds to application layer.

<img src='http://neek-klondike.googlecode.com/svn/wiki/sw-design.png' alt='Layered architecture of NEEK Klondike' height='600' width='800'>

Figure 1 - Packages KLONDIKE and NEEK<br>
<br>
<h1>NEEK package</h1>

This package is the wrapper for several low-level C-libraries, which are provided by Altera and are described in note <a href='http://www.altera.com/literature/an/an527.pdf'>Implementing an LCD Controller</a>.<br>
Main class of this package, which is responsible for straight communicating with the C-libraries is <a href='https://code.google.com/p/neek-klondike/source/browse/software/neek/LCDTouchscreen.hpp'>LCDTouchscreen</a>.<br>
The class LCDTouchscreen allows to control LCD touch-screen using the two pairs of methods.<br>
First pair of methods allows to register components which will be displayed on LCD or will handle touch-screen's events.<br>
These components should implement interface <a href='https://code.google.com/p/neek-klondike/source/browse/software/neek/Displayable.hpp'>Displayable</a> and/or <a href='https://code.google.com/p/neek-klondike/source/browse/software/neek/Touchable.hpp'>Touchable</a>.<br>
Second pair of methods is responsible for updating LCD's content and generating of touch-screen's events.<br>
Both of these methods use the same mechanism: when display's content should be regenerated or when clients should be notified about the touch-screen's event, an appropriate method of the callback interface will be called for all registered components.<br>
<br>
<h2>Displaying information on the LCD</h2>

Class <a href='https://code.google.com/p/neek-klondike/source/browse/software/neek/Graphics.hpp'>Graphics</a> is designed to simplify process of LCD's content refresh and also this class is high-level interface for displaying components.<br>
In this application we perform only two actions: clearing of display and drawing a bitmap.<br>
Therefore, a class to represent bitmaps is needed.<br>
At this moment we provide class <a href='https://code.google.com/p/neek-klondike/source/browse/software/neek/Bitmap.hpp'>Bitmap</a> which is the wrapper over low-level representation of bitmap.<br>
This class not provides any methods and its data could be accessed only by class Graphics through the friendship relations.<br>
<br>
<h1>KLONDIKE package</h1>

KLONDIKE package contains only three classes which are used to implement game on the basis of NEEK package.<br>
First class <a href='https://code.google.com/p/neek-klondike/source/browse/software/klondike/Card.cpp'>Card</a> is the simple read-only value object that represents playing card.<br>
For designed game we need the standard deck of 52 playing cards.<br>
To specify all of cards in the deck we introduced enumerations of ranks and suits (notably <a href='https://code.google.com/p/neek-klondike/source/browse/software/klondike/Card.cpp'>CardRank</a> and <a href='https://code.google.com/p/neek-klondike/source/browse/software/klondike/Card.cpp'>CardSuit</a>).<br>
<br>
<blockquote><i>Each of these enumerations contains additional element for the situation when default constructor was used (viz <a href='https://code.google.com/p/neek-klondike/source/browse/software/klondike/Card.cpp'>CardRank_Unknown</a> and <a href='https://code.google.com/p/neek-klondike/source/browse/software/klondike/Card.cpp'>CardSuit_Unknown</a>).</i>
<i>Default constructor is required for compatibility with standard containers, when this feature will not be required, this constructor should be dropped (and also additional elements of ranks and suits enumerations).</i></blockquote>

Second class represents <a href='https://code.google.com/p/neek-klondike/source/browse/software/klondike/Deck.cpp'>Deck</a> of playing cards.<br>
This class is the domain-specific container which works like stack.<br>
At last, third class <a href='https://code.google.com/p/neek-klondike/source/browse/software/klondike/Layout.cpp'>Layout</a> implements logic of game and  also it is responsible for displaying of game layout and processing of touch-sreen's events.<br>
Therefore, it implements interfaces Displayable and Touchable from the package NEEK.