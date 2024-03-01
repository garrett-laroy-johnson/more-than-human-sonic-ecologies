#include "daisy_2dtechno_2dmachine.h"

namespace daisy_2dtechno_2dmachine {

/****************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER 200k USD in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below 200k USD annual revenue or funding.

For entities with OVER 200k USD in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing (at) cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/360050779193-Gen-Code-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
****************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Change __m_change_15;
	Change __m_change_14;
	Change __m_change_48;
	Change __m_change_17;
	Change __m_change_12;
	Change __m_change_55;
	Change __m_change_62;
	Change __m_change_20;
	Change __m_change_27;
	Change __m_change_34;
	Change __m_change_69;
	Change __m_change_41;
	Delta __m_delta_13;
	Phasor __m_phasor_11;
	PlusEquals __m_pluseq_16;
	SineCycle __m_cycle_33;
	SineCycle __m_cycle_47;
	SineCycle __m_cycle_26;
	SineCycle __m_cycle_19;
	SineCycle __m_cycle_40;
	SineCycle __m_cycle_68;
	SineCycle __m_cycle_61;
	SineCycle __m_cycle_54;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample __m_slide_43;
	t_sample __m_latch_42;
	t_sample __m_latch_46;
	t_sample __m_latch_67;
	t_sample __m_latch_63;
	t_sample __m_latch_49;
	t_sample __m_latch_53;
	t_sample __m_slide_64;
	t_sample __m_slide_57;
	t_sample __m_slide_50;
	t_sample __m_latch_60;
	t_sample __m_latch_56;
	t_sample __m_latch_28;
	t_sample __m_slide_36;
	t_sample m_history_5;
	t_sample m_history_6;
	t_sample m_history_7;
	t_sample m_knob_8;
	t_sample m_history_4;
	t_sample m_history_2;
	t_sample m_history_3;
	t_sample samplerate;
	t_sample m_history_1;
	t_sample __m_latch_39;
	t_sample m_knob_9;
	t_sample samples_to_seconds;
	t_sample __m_slide_29;
	t_sample __m_latch_32;
	t_sample __m_latch_35;
	t_sample m_button_10;
	t_sample __m_latch_70;
	t_sample __m_slide_22;
	t_sample __m_latch_25;
	t_sample __m_latch_18;
	t_sample __m_latch_21;
	t_sample __m_slide_71;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_knob_8 = ((int)0);
		m_knob_9 = ((int)0);
		m_button_10 = ((int)0);
		samples_to_seconds = (1 / samplerate);
		__m_phasor_11.reset(0);
		__m_change_12.reset(0);
		__m_delta_13.reset(0);
		__m_change_14.reset(0);
		__m_change_15.reset(0);
		__m_pluseq_16.reset(0);
		__m_change_17.reset(0);
		__m_latch_18 = 0;
		__m_cycle_19.reset(samplerate, 0);
		__m_change_20.reset(0);
		__m_latch_21 = 0;
		__m_slide_22 = 0;
		__m_latch_25 = 0;
		__m_cycle_26.reset(samplerate, 0);
		__m_change_27.reset(0);
		__m_latch_28 = 0;
		__m_slide_29 = 0;
		__m_latch_32 = 0;
		__m_cycle_33.reset(samplerate, 0);
		__m_change_34.reset(0);
		__m_latch_35 = 0;
		__m_slide_36 = 0;
		__m_latch_39 = 0;
		__m_cycle_40.reset(samplerate, 0);
		__m_change_41.reset(0);
		__m_latch_42 = 0;
		__m_slide_43 = 0;
		__m_latch_46 = 0;
		__m_cycle_47.reset(samplerate, 0);
		__m_change_48.reset(0);
		__m_latch_49 = 0;
		__m_slide_50 = 0;
		__m_latch_53 = 0;
		__m_cycle_54.reset(samplerate, 0);
		__m_change_55.reset(0);
		__m_latch_56 = 0;
		__m_slide_57 = 0;
		__m_latch_60 = 0;
		__m_cycle_61.reset(samplerate, 0);
		__m_change_62.reset(0);
		__m_latch_63 = 0;
		__m_slide_64 = 0;
		__m_latch_67 = 0;
		__m_cycle_68.reset(samplerate, 0);
		__m_change_69.reset(0);
		__m_latch_70 = 0;
		__m_slide_71 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		samples_to_seconds = (1 / samplerate);
		t_sample history_15837_next_15864 = fixdenorm(((t_sample)0.5));
		int int_10285 = int(m_button_10);
		t_sample iup_23 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_24 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_30 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_31 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_37 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_38 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_44 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_45 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_51 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_52 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_58 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_59 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_65 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_66 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_72 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_73 = (1 / maximum(1, abs(((int)0))));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample phasor_32782 = __m_phasor_11(((t_sample)1.2333333333333), samples_to_seconds);
			t_sample mul_15842 = (phasor_32782 * ((int)2));
			t_sample sub_13005 = (phasor_32782 - m_history_7);
			t_sample add_13006 = (phasor_32782 + m_history_7);
			t_sample div_13004 = safediv(sub_13005, add_13006);
			t_sample abs_13003 = fabs(div_13004);
			int gt_13001 = (abs_13003 > ((t_sample)0.5));
			int change_13000 = __m_change_12(gt_13001);
			int gt_12999 = (change_13000 > ((int)0));
			int gen_15852 = gt_12999;
			t_sample history_13002_next_13007 = fixdenorm(phasor_32782);
			t_sample delta_15858 = __m_delta_13(phasor_32782);
			t_sample wrap_15859 = wrap(delta_15858, (-0.5), ((t_sample)0.5));
			t_sample gen_15860 = wrap_15859;
			t_sample mul_15855 = (gen_15860 * ((int)2));
			t_sample add_15853 = (mul_15855 + m_history_4);
			t_sample sub_15840 = (add_15853 - mul_15842);
			t_sample round_15851 = (trunc((sub_15840 * ((t_sample)0.5))) * ((int)2));
			t_sample add_15841 = (round_15851 + mul_15842);
			t_sample sub_15862 = (m_history_5 - ((t_sample)0.5));
			t_sample add_15863 = (m_history_5 + ((t_sample)0.5));
			t_sample div_15861 = safediv(sub_15862, add_15863);
			t_sample abs_15835 = fabs(div_15861);
			int gt_15836 = (abs_15835 > ((t_sample)0.015625));
			int and_15839 = (gt_15836 && ((int)1));
			t_sample switch_15843 = (and_15839 ? and_15839 : m_history_6);
			t_sample switch_15846 = (gen_15852 ? switch_15843 : ((int)0));
			t_sample gen_15849 = switch_15846;
			t_sample switch_15845 = (switch_15846 ? ((int)0) : switch_15843);
			t_sample history_15847_next_15848 = fixdenorm(switch_15845);
			int or_15838 = (gen_15849 || ((int)0));
			t_sample switch_15857 = (or_15838 ? add_15841 : add_15853);
			t_sample wrap_15854 = wrap(switch_15857, ((int)0), ((int)1));
			t_sample gen_32659 = wrap_15854;
			t_sample history_15856_next_15865 = fixdenorm(wrap_15854);
			t_sample wrap_32661 = wrap(gen_32659, ((int)0), ((int)1));
			t_sample sub_33066 = (wrap_32661 - m_history_3);
			t_sample add_33071 = (wrap_32661 + m_history_3);
			t_sample div_33072 = safediv(sub_33066, add_33071);
			t_sample abs_33069 = fabs(div_33072);
			int gt_33073 = (abs_33069 > ((t_sample)0.5));
			int change_33070 = __m_change_14(gt_33073);
			int gt_33067 = (change_33070 > ((int)0));
			int gen_32660 = gt_33067;
			t_sample history_13002_next_33065 = fixdenorm(wrap_32661);
			t_sample sub_33075 = (gen_32660 - m_history_2);
			t_sample add_33080 = (gen_32660 + m_history_2);
			t_sample div_33081 = safediv(sub_33075, add_33080);
			t_sample abs_33083 = fabs(div_33081);
			int gt_33078 = (abs_33083 > ((t_sample)0.5));
			int change_33077 = __m_change_15(gt_33078);
			int gt_33076 = (change_33077 > ((int)0));
			int gen_13008 = gt_33076;
			t_sample history_13002_next_33079 = fixdenorm(gen_32660);
			t_sample plusequals_12998 = __m_pluseq_16.post(safediv(8, samplerate), gen_13008, 0);
			t_sample clamp_12997 = ((plusequals_12998 <= ((int)0)) ? ((int)0) : ((plusequals_12998 >= ((int)1)) ? ((int)1) : plusequals_12998));
			t_sample sub_33260 = (clamp_12997 - ((int)0));
			t_sample scale_33257 = ((safepow((sub_33260 * ((t_sample)1)), (1 * ((t_sample)0.25))) * ((int)-1)) + ((int)1));
			t_sample scale_13009 = scale_33257;
			t_sample sub_33264 = (scale_13009 - ((int)1));
			t_sample scale_33261 = ((safepow((sub_33264 * ((t_sample)-1)), ((int)1)) * ((int)-100)) + ((int)150));
			t_sample scale_13012 = scale_33261;
			t_sample sin_13013 = sin(scale_13012);
			t_sample mul_13014 = (scale_13009 * sin_13013);
			t_sample mix_33265 = (mul_13014 + (((t_sample)0.9) * (m_history_1 - mul_13014)));
			t_sample mix_13011 = mix_33265;
			t_sample gen_32663 = mix_13011;
			t_sample history_13010_next_13015 = fixdenorm(mix_13011);
			t_sample mul_32662 = (m_knob_9 * gen_32663);
			t_sample mul_32656 = (mul_32662 * ((t_sample)0.25));
			t_sample mul_32781 = (phasor_32782 * ((int)8));
			t_sample floor_32780 = floor(mul_32781);
			int eq_32739 = (floor_32780 == ((int)5));
			int eq_32709 = (floor_32780 == ((int)4));
			int eq_32729 = (floor_32780 == ((int)6));
			int eq_32759 = (floor_32780 == ((int)2));
			int eq_32779 = (floor_32780 == ((int)0));
			int eq_32719 = (floor_32780 == ((int)7));
			int eq_32749 = (floor_32780 == ((int)3));
			int eq_32769 = (floor_32780 == ((int)1));
			t_sample noise_32704 = noise();
			t_sample noise_32724 = noise();
			t_sample noise_32754 = noise();
			t_sample noise_32774 = noise();
			t_sample noise_32734 = noise();
			t_sample noise_32714 = noise();
			t_sample noise_32744 = noise();
			t_sample noise_32764 = noise();
			int change_10286 = __m_change_17(int_10285);
			int eqp_10287 = ((int_10285 == change_10286) ? int_10285 : 0);
			__m_latch_18 = ((eqp_10287 != 0) ? noise_32734 : __m_latch_18);
			t_sample latch_32731 = __m_latch_18;
			t_sample sub_33269 = (latch_32731 - (-1));
			t_sample scale_33266 = ((safepow((sub_33269 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_32732 = mtof(scale_33266, ((int)440));
			__m_cycle_19.freq(mtof_32732);
			t_sample cycle_32737 = __m_cycle_19(__sinedata);
			t_sample cycleindex_32738 = __m_cycle_19.phase();
			int gt_33 = (cycle_32737 > ((int)0));
			int change_32 = __m_change_20(gt_33);
			__m_latch_21 = ((change_32 != 0) ? eq_32739 : __m_latch_21);
			int latch_31 = __m_latch_21;
			__m_slide_22 = fixdenorm((__m_slide_22 + (((latch_31 > __m_slide_22) ? iup_23 : idown_24) * (latch_31 - __m_slide_22))));
			t_sample slide_30 = __m_slide_22;
			t_sample mul_34 = (cycle_32737 * slide_30);
			t_sample mul_32671 = (mul_34 * ((t_sample)0.25));
			__m_latch_25 = ((eqp_10287 != 0) ? noise_32704 : __m_latch_25);
			t_sample latch_32701 = __m_latch_25;
			t_sample sub_33273 = (latch_32701 - (-1));
			t_sample scale_33270 = ((safepow((sub_33273 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_32702 = mtof(scale_33270, ((int)440));
			__m_cycle_26.freq(mtof_32702);
			t_sample cycle_32707 = __m_cycle_26(__sinedata);
			t_sample cycleindex_32708 = __m_cycle_26.phase();
			int gt_33086 = (cycle_32707 > ((int)0));
			int change_33085 = __m_change_27(gt_33086);
			__m_latch_28 = ((change_33085 != 0) ? eq_32709 : __m_latch_28);
			int latch_33090 = __m_latch_28;
			__m_slide_29 = fixdenorm((__m_slide_29 + (((latch_33090 > __m_slide_29) ? iup_30 : idown_31) * (latch_33090 - __m_slide_29))));
			t_sample slide_33089 = __m_slide_29;
			t_sample mul_33091 = (cycle_32707 * slide_33089);
			t_sample mul_32672 = (mul_33091 * ((t_sample)0.25));
			__m_latch_32 = ((eqp_10287 != 0) ? noise_32724 : __m_latch_32);
			t_sample latch_32721 = __m_latch_32;
			t_sample sub_33277 = (latch_32721 - (-1));
			t_sample scale_33274 = ((safepow((sub_33277 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_32722 = mtof(scale_33274, ((int)440));
			__m_cycle_33.freq(mtof_32722);
			t_sample cycle_32727 = __m_cycle_33(__sinedata);
			t_sample cycleindex_32728 = __m_cycle_33.phase();
			int gt_33093 = (cycle_32727 > ((int)0));
			int change_33092 = __m_change_34(gt_33093);
			__m_latch_35 = ((change_33092 != 0) ? eq_32729 : __m_latch_35);
			int latch_33095 = __m_latch_35;
			__m_slide_36 = fixdenorm((__m_slide_36 + (((latch_33095 > __m_slide_36) ? iup_37 : idown_38) * (latch_33095 - __m_slide_36))));
			t_sample slide_33097 = __m_slide_36;
			t_sample mul_33098 = (cycle_32727 * slide_33097);
			t_sample mul_32670 = (mul_33098 * ((t_sample)0.25));
			__m_latch_39 = ((eqp_10287 != 0) ? noise_32754 : __m_latch_39);
			t_sample latch_32751 = __m_latch_39;
			t_sample sub_33281 = (latch_32751 - (-1));
			t_sample scale_33278 = ((safepow((sub_33281 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_32752 = mtof(scale_33278, ((int)440));
			__m_cycle_40.freq(mtof_32752);
			t_sample cycle_32757 = __m_cycle_40(__sinedata);
			t_sample cycleindex_32758 = __m_cycle_40.phase();
			int gt_33100 = (cycle_32757 > ((int)0));
			int change_33099 = __m_change_41(gt_33100);
			__m_latch_42 = ((change_33099 != 0) ? eq_32759 : __m_latch_42);
			int latch_33102 = __m_latch_42;
			__m_slide_43 = fixdenorm((__m_slide_43 + (((latch_33102 > __m_slide_43) ? iup_44 : idown_45) * (latch_33102 - __m_slide_43))));
			t_sample slide_33104 = __m_slide_43;
			t_sample mul_33105 = (cycle_32757 * slide_33104);
			t_sample mul_32666 = (mul_33105 * ((t_sample)0.25));
			__m_latch_46 = ((eqp_10287 != 0) ? noise_32774 : __m_latch_46);
			t_sample latch_32771 = __m_latch_46;
			t_sample sub_33285 = (latch_32771 - (-1));
			t_sample scale_33282 = ((safepow((sub_33285 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_32772 = mtof(scale_33282, ((int)440));
			__m_cycle_47.freq(mtof_32772);
			t_sample cycle_32777 = __m_cycle_47(__sinedata);
			t_sample cycleindex_32778 = __m_cycle_47.phase();
			int gt_33107 = (cycle_32777 > ((int)0));
			int change_33106 = __m_change_48(gt_33107);
			__m_latch_49 = ((change_33106 != 0) ? eq_32779 : __m_latch_49);
			int latch_33109 = __m_latch_49;
			__m_slide_50 = fixdenorm((__m_slide_50 + (((latch_33109 > __m_slide_50) ? iup_51 : idown_52) * (latch_33109 - __m_slide_50))));
			t_sample slide_33111 = __m_slide_50;
			t_sample mul_33112 = (cycle_32777 * slide_33111);
			t_sample mul_32668 = (mul_33112 * ((t_sample)0.25));
			t_sample l_32675 = (((mul_32668 + mul_32666) + mul_32670) + mul_32672);
			t_sample sub_32655 = (l_32675 - mul_32656);
			t_sample out1 = (mul_32662 + sub_32655);
			__m_latch_53 = ((eqp_10287 != 0) ? noise_32714 : __m_latch_53);
			t_sample latch_32711 = __m_latch_53;
			t_sample sub_33289 = (latch_32711 - (-1));
			t_sample scale_33286 = ((safepow((sub_33289 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_32712 = mtof(scale_33286, ((int)440));
			__m_cycle_54.freq(mtof_32712);
			t_sample cycle_32717 = __m_cycle_54(__sinedata);
			t_sample cycleindex_32718 = __m_cycle_54.phase();
			int gt_33114 = (cycle_32717 > ((int)0));
			int change_33113 = __m_change_55(gt_33114);
			__m_latch_56 = ((change_33113 != 0) ? eq_32719 : __m_latch_56);
			int latch_33116 = __m_latch_56;
			__m_slide_57 = fixdenorm((__m_slide_57 + (((latch_33116 > __m_slide_57) ? iup_58 : idown_59) * (latch_33116 - __m_slide_57))));
			t_sample slide_33118 = __m_slide_57;
			t_sample mul_33119 = (cycle_32717 * slide_33118);
			t_sample mul_32669 = (mul_33119 * ((t_sample)0.25));
			__m_latch_60 = ((eqp_10287 != 0) ? noise_32744 : __m_latch_60);
			t_sample latch_32741 = __m_latch_60;
			t_sample sub_33293 = (latch_32741 - (-1));
			t_sample scale_33290 = ((safepow((sub_33293 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_32742 = mtof(scale_33290, ((int)440));
			__m_cycle_61.freq(mtof_32742);
			t_sample cycle_32747 = __m_cycle_61(__sinedata);
			t_sample cycleindex_32748 = __m_cycle_61.phase();
			int gt_33121 = (cycle_32747 > ((int)0));
			int change_33120 = __m_change_62(gt_33121);
			__m_latch_63 = ((change_33120 != 0) ? eq_32749 : __m_latch_63);
			int latch_33123 = __m_latch_63;
			__m_slide_64 = fixdenorm((__m_slide_64 + (((latch_33123 > __m_slide_64) ? iup_65 : idown_66) * (latch_33123 - __m_slide_64))));
			t_sample slide_33125 = __m_slide_64;
			t_sample mul_33126 = (cycle_32747 * slide_33125);
			t_sample mul_32665 = (mul_33126 * ((t_sample)0.25));
			__m_latch_67 = ((eqp_10287 != 0) ? noise_32764 : __m_latch_67);
			t_sample latch_32761 = __m_latch_67;
			t_sample sub_33297 = (latch_32761 - (-1));
			t_sample scale_33294 = ((safepow((sub_33297 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_32762 = mtof(scale_33294, ((int)440));
			__m_cycle_68.freq(mtof_32762);
			t_sample cycle_32767 = __m_cycle_68(__sinedata);
			t_sample cycleindex_32768 = __m_cycle_68.phase();
			int gt_33128 = (cycle_32767 > ((int)0));
			int change_33127 = __m_change_69(gt_33128);
			__m_latch_70 = ((change_33127 != 0) ? eq_32769 : __m_latch_70);
			int latch_33130 = __m_latch_70;
			__m_slide_71 = fixdenorm((__m_slide_71 + (((latch_33130 > __m_slide_71) ? iup_72 : idown_73) * (latch_33130 - __m_slide_71))));
			t_sample slide_33132 = __m_slide_71;
			t_sample mul_33133 = (cycle_32767 * slide_33132);
			t_sample mul_32667 = (mul_33133 * ((t_sample)0.25));
			t_sample r_32674 = (((mul_32667 + mul_32665) + mul_32669) + mul_32671);
			t_sample sub_32657 = (r_32674 - mul_32656);
			t_sample out2 = (mul_32662 + sub_32657);
			m_history_7 = history_13002_next_13007;
			m_history_4 = history_15856_next_15865;
			m_history_5 = history_15837_next_15864;
			m_history_6 = history_15847_next_15848;
			m_history_3 = history_13002_next_33065;
			m_history_2 = history_13002_next_33079;
			m_history_1 = history_13010_next_13015;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_knob1(t_param _value) {
		m_knob_8 = (_value < 40 ? 40 : (_value > 200 ? 200 : _value));
	};
	inline void set_knob2(t_param _value) {
		m_knob_9 = (_value < 0 ? 0 : (_value > 0.5 ? 0.5 : _value));
	};
	inline void set_button(t_param _value) {
		m_button_10 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 3; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_button(value); break;
		case 1: self->set_knob1(value); break;
		case 2: self->set_knob2(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_button_10; break;
		case 1: *value = self->m_knob_8; break;
		case 2: *value = self->m_knob_9; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(3 * sizeof(ParamInfo));
	self->__commonstate.numparams = 3;
	// initialize parameter 0 ("m_button_10")
	pi = self->__commonstate.params + 0;
	pi->name = "button";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_button_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob_8")
	pi = self->__commonstate.params + 1;
	pi->name = "knob1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 40;
	pi->outputmax = 200;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob_9")
	pi = self->__commonstate.params + 2;
	pi->name = "knob2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.5;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // daisy_2dtechno_2dmachine::
