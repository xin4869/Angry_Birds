Instructions for using/making level files!

File format:

- '#' marks a comment (has to be at start of line)
    - \# e.g. comment here
- Basic idea is Classname/defaultsName, x, y, rotation
    - x, y is the center of the object
    - rotation (optional) in degrees
        - object is rotated around center
- File is case-insensitive
- Extra spaces, extra text (at end of line), empty lines and bad lines will be ignored

- Level requires at least:
    - 1 bird
    - 1 pig
    - Realistically some blocks
        - To simplify level creation, a fixed ground will be automatically added below y=0 from x=-100 to x=100 (m)

Adding objects:

- Birds:
    - Classname
        - List of birds that can be shot, in this order
        - Whether/how to display unshot birds is left to rendering
        - Them being physics objects before launch could lead to unusual behaviour (e.g. falling off the map)

- Pigs:
    - NormalPig, x, y, rotation
    - IronPig, x, y
    - etc., name from default values

- Blocks:
    - DefaultsName, x, y, rotation
    - e.g.:
    - IceCircleS, x, y, rot
    - WoodSquare, x, y
    - etc.

Settings format:
- Given a setting multiple times the last one will be selected
- Gravity, x, y
    - Default is 0, -10 if omitted
- Slingshot, x, y
    - Default is 0, 2 if omitted
- ScoreLimits, 1*, 2*, 3*
    - Score limits for stars
    - Defaults are <*reasonable defaults*> if omitted
    - Recommended to set these