
class status_change
{
      public:
          status_change();
          ~status_change();

          void reset();

          int code_number;
          int modify_number;
          int impact_direction;
          int x;
          int y;
};

status_change::status_change()
{
    code_number = 0;
    modify_number = 0;
    impact_direction = 0;
    x = 0;
    y = 0;
}

status_change::~status_change()
{
    code_number = 0;
    modify_number = 0;
    impact_direction = 0;
    x = 0;
    y = 0;
}

void status_change::reset()
{
    code_number = 0;
    modify_number = 0;
    impact_direction = 0;
    x = 0;
    y = 0;
}
