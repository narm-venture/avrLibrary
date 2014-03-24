//select refrence voltage mode
//select which adc you want to use
//start conversion
//take result in result_data
#ifndef ADC_2298
#define ADC_2298
  #include <my_utils/delay_2298.h>
  #include <my_utils/adc_2298.h>
void ref_volt_external(void);
void ref_volt_int_2_56(void);
void select_adc(unsigned int);
void start_conversion(void);
void result_data_mode(unsigned int);
#endif