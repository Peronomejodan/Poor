This is the fundamental of making a teleporter for TrinityCore using SmartAI!

I've not added locations, as I'm not doing your job. You need to learn, kiddo!
I lied. I've added two locations, for you to see the fundamentals.

To add more teleport locations, simply create a new row in gossip_menu_option,
 and set the entry as the templates ones.(60001) 

Set the ID to 3, as this will be the third location you'll be making. 
Follow the two templates, that's been following you.


Now go to smart_scripts, and copy the existing row of a teleport location.
Set ID to 3, as it's the third location. 

Even_param1 is attaching the Gossip_menu table, so it's universal for the whole teleporter.

Event_param2 is the ID of the gossip options. Make this 3, as it's the third teleport location. 

Action_param1 is what map it is. (0 Kalimdor, 1 azeroth) etc etc. 

Now to the whole location part. target_x, y, x, o is the actually location youll be teleported to.

(Unsure of what the coordinates is? Go in-game and go to the spot you wanted to be teleported, and type .gps  (the coordinates will show).


And then, I guess you're pretty much done.

Goodluck!

If you're in need of any help,
You can find me on Discord.

Authoritah#1901
