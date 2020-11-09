#ifndef PARAMS_H
#define PARAMS_H

#define HARE_SPEED 5
#define TURT_SPEED 1
#define RACE_DIST 100
#define MAX_GAP 10
#define PRINT_INTERVAL 5e5
#define START_DELAY 2e6

#define a2r_read a2r[0]
#define a2r_write a2r[1]
#define a2g_read a2g[0]
#define a2g_write a2g[1]
#define a2t_read a2t[0]
#define a2t_write a2t[1]
#define a2h_read a2h[0]
#define a2h_write a2h[1]

#define race_state_changed ((race -> hare_pos != prev_state -> hare_pos) || (race -> turt_pos != prev_state -> turt_pos))
#define hare_should_sleep (race -> hare_pos - race -> turt_pos >= race -> dist_threshold)
#define hare_won (race -> hare_time < race -> turt_time)
#define turt_won (race -> hare_time > race -> turt_time)
#define hare_completed (race -> hare_pos >= race -> distance)
#define turt_completed (race -> turt_pos >= race -> distance)
#endif
