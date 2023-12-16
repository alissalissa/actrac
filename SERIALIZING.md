# Serialization
## Document Purpose
This document outlines the format in which data stored by this program is written to and read from files.

## Section 1: Magic Number
This section starts with a magic number: 0xEE
The presence of this magic number indicates that the file is un-corrupted, although subsequent checks in the read process confirm this to be the case as well.

## Section 2: Tag Information
The next thing to be encoded is the cache of used tags.
This section is comprised of the length in bytes (a series of chars) of the entire section, followed by the indicated number of bytes.  The stream of bytes consists of tags separated by line feeds (0x0A).  The section ends with an indicator (0x0d).

## Section 3: Date Information
What follows is the number of dates in the date record section, written as an int32_t.  Thence:<br>
&nbsp;&nbsp;&nbsp;&nbsp;1) The date, formatted as MM/DD/YYYY, followed by the information for the activities from that date.  The activity information is formatted as an indicator (0x0c), followed by:<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;a) ID<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;b) Label<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;c) The number of tags associated with this activity written as a size_t<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;d) Each tag, followed by 0x0b<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;e) The number of hours as a float<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;f) a single byte, 0x01 for confirmed activity, 0x00 for an unconfirmed activity<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;g) an int32 indicating the number of recurrences<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;h) an int32 indicating the number of days over which an activity should repeat<br>
&nbsp;&nbsp;&nbsp;&nbsp;2) Each activity is seperated by an indicator (0x0c)<br>
&nbsp;&nbsp;&nbsp;&nbsp;3) Each date is separated by an indicator (0x0d)<br>

## End
The end of the file ends with the magic number to indicate proper tracking / lack of file corruption.