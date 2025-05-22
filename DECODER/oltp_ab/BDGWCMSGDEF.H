#ifndef WCMSG_H
#define WCMSG_H


// RDC request from WC
#define WCMSG_CODE_NONE     0       // function code not decided
#define WCMSG_CODE_MTGINP   301     // new meeting schedule
#define WCMSG_CODE_MTGRCC   302     // race close interval
#define WCMSG_CODE_PARRCW   303     // race close warning interval
#define WCMSG_CODE_MTGBSI   304     // change of bad sale interval
#define WCMSG_CODE_MTGSRS   305     // start sell all pools in a meeting
#define WCMSG_CODE_MTGSPS   306     // stop sell all pools in a meeting
#define WCMSG_CODE_RCESPS   307     // stop sell W/P/Q/QP or all pools in a race
#define WCMSG_CODE_RCESPP   308     // stop pay all pools in a race
#define WCMSG_CODE_POLSRS   309     // start sell a pool
#define WCMSG_CODE_POLSPS   310     // stop sell a pool
#define WCMSG_CODE_POLSPP   311     // stop pay pool
#define WCMSG_CODE_RCESUB   312     // race substitutes
#define WCMSG_CODE_RCESCR   313     // race scratch runner
#define WCMSG_CODE_RCERES   314     // race results
#define WCMSG_CODE_RCEPTT   315     // race post time 
#define WCMSG_CODE_RCECLS   316     // race close
#define WCMSG_CODE_POLRAD   317     // pool result and dividend
#define WCMSG_CODE_RCEAPP   318     // all-up post race pass
#define WCMSG_CODE_POLRFD   319     // pool refund
#define WCMSG_CODE_POLCRF   320     // cancel pool refund
#define WCMSG_CODE_PARAUE   321     // enable/disable all-up formulae
#define WCMSG_CODE_PARAUF   322     // allup formulae
#define WCMSG_CODE_RCEEAU   323     // enable/disable allup betting in a race
#define WCMSG_CODE_PARAUW   324     // aup reinvestment warning limit 
#define WCMSG_CODE_MTGABN   325     // abandon meeting
#define WCMSG_CODE_PARMBV   326     // max. bet value
#define WCMSG_CODE_PARPHL   327     // pay out limits
#define WCMSG_CODE_PARTBD   328     // telebet deposit parameters
#define WCMSG_CODE_PARTBW   329     // telebet withdrawal parameters
#define WCMSG_CODE_PARCRE   330     // enable/disable deposit betting
#define WCMSG_CODE_PAREMC   331     // EFT min. cash voucher amount
#define WCMSG_CODE_PARNBD   332     // next business date
#define WCMSG_CODE_PARPHB   333     // peak hour min. bet 
#define WCMSG_CODE_PARLBV   334     // large bet values
#define WCMSG_CODE_PARLDV   335     // large dividend values
#define WCMSG_CODE_LOTINP   336     // new lottery schedule
#define WCMSG_CODE_LOTDDT   337     // change of lottery draw date
#define WCMSG_CODE_LOTODT   338     // change of lottery opening date
#define WCMSG_CODE_LOTCDT   339     // change of lottery closing date time
#define WCMSG_CODE_LOTSRS   340     // start sell lottery
#define WCMSG_CODE_LOTSPS   341     // stop sell lottery
#define WCMSG_CODE_LOTRES   342     // lottery result
#define WCMSG_CODE_LOTPRZ   343     // lottery prize
#define WCMSG_CODE_LOTSPP   344     // stop pay lottery prize
#define WCMSG_CODE_LOTCLM   345     // claim lottery prize
#define WCMSG_CODE_LOTCCM   346     // cancel claim on lottery prize
#define WCMSG_CODE_PARLBS   347     // lottery bad sale interval
#define WCMSG_CODE_PARLCW   348     // lottery close warning interval
#define WCMSG_CODE_LOTSRN   349     // lottery selection range
#define WCMSG_CODE_LOTUNI   350     // lottery unit bet
#define WCMSG_CODE_LOTCEN   351     // lottery ccgame enable/disable selling
#define WCMSG_CODE_PARCVE   352     // CV Encashment 
#define WCMSG_CODE_LSCMTG   353     // losing amount consolation control - meeting 
#define WCMSG_CODE_LSCRCE   354     // losing amount consolation control - race
#define WCMSG_CODE_LSCPOL   355     // losing amount consolation control - pool
#define WCMSG_CODE_PAREXB   356     // enable/disable external branch
#define WCMSG_CODE_LOTMER   357     // lottery draw merge // CS03
                         
#endif