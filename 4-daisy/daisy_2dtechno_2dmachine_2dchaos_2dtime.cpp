#include "daisy_2dtechno_2dmachine_2dchaos_2dtime.h"

namespace daisy_2dtechno_2dmachine_2dchaos_2dtime {

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
	Change __m_change_25;
	Change __m_change_26;
	Change __m_change_71;
	Change __m_change_64;
	Change __m_change_29;
	Change __m_change_50;
	Change __m_change_21;
	Change __m_change_20;
	Change __m_change_57;
	Change __m_change_78;
	Change __m_change_36;
	Change __m_change_22;
	Change __m_change_43;
	PlusEquals __m_pluseq_23;
	SineCycle __m_cycle_49;
	SineCycle __m_cycle_42;
	SineCycle __m_cycle_56;
	SineCycle __m_cycle_63;
	SineCycle __m_cycle_28;
	SineCycle __m_cycle_77;
	SineCycle __m_cycle_35;
	SineCycle __m_cycle_70;
	SineData __sinedata;
	int vectorsize;
	int __exception;
	t_sample __m_slide_45;
	t_sample __m_latch_44;
	t_sample __m_latch_48;
	t_sample __m_slide_52;
	t_sample __m_latch_55;
	t_sample __m_latch_72;
	t_sample __m_latch_69;
	t_sample __m_slide_73;
	t_sample __m_latch_76;
	t_sample __m_latch_51;
	t_sample __m_slide_66;
	t_sample __m_latch_62;
	t_sample __m_latch_65;
	t_sample __m_latch_58;
	t_sample __m_slide_59;
	t_sample __m_latch_41;
	t_sample __m_slide_31;
	t_sample __m_latch_37;
	t_sample m_y_7;
	t_sample m_z_6;
	t_sample m_x_8;
	t_sample m_history_10;
	t_sample m_history_9;
	t_sample m_history_11;
	t_sample m_history_5;
	t_sample m_history_3;
	t_sample samplerate;
	t_sample m_history_4;
	t_sample m_history_1;
	t_sample m_history_2;
	t_sample __m_slide_38;
	t_sample m_history_12;
	t_sample m_history_14;
	t_sample __m_latch_30;
	t_sample __m_latch_27;
	t_sample __m_latch_79;
	t_sample __m_latch_34;
	t_sample m_history_13;
	t_sample elapsed;
	t_sample m_knob_18;
	t_sample m_history_15;
	t_sample m_button_19;
	t_sample m_beats_16;
	t_sample m_knob_17;
	t_sample __m_slide_80;
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
		m_z_6 = ((int)0);
		m_y_7 = ((int)0);
		m_x_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		m_history_13 = ((int)0);
		m_history_14 = ((int)0);
		m_history_15 = ((int)0);
		m_beats_16 = ((int)4);
		m_knob_17 = ((int)0);
		m_knob_18 = ((int)0);
		m_button_19 = ((int)0);
		__m_change_20.reset(0);
		__m_change_21.reset(0);
		__m_change_22.reset(0);
		__m_pluseq_23.reset(0);
		elapsed = 0;
		__m_change_25.reset(0);
		__m_change_26.reset(0);
		__m_latch_27 = 0;
		__m_cycle_28.reset(samplerate, 0);
		__m_change_29.reset(0);
		__m_latch_30 = 0;
		__m_slide_31 = 0;
		__m_latch_34 = 0;
		__m_cycle_35.reset(samplerate, 0);
		__m_change_36.reset(0);
		__m_latch_37 = 0;
		__m_slide_38 = 0;
		__m_latch_41 = 0;
		__m_cycle_42.reset(samplerate, 0);
		__m_change_43.reset(0);
		__m_latch_44 = 0;
		__m_slide_45 = 0;
		__m_latch_48 = 0;
		__m_cycle_49.reset(samplerate, 0);
		__m_change_50.reset(0);
		__m_latch_51 = 0;
		__m_slide_52 = 0;
		__m_latch_55 = 0;
		__m_cycle_56.reset(samplerate, 0);
		__m_change_57.reset(0);
		__m_latch_58 = 0;
		__m_slide_59 = 0;
		__m_latch_62 = 0;
		__m_cycle_63.reset(samplerate, 0);
		__m_change_64.reset(0);
		__m_latch_65 = 0;
		__m_slide_66 = 0;
		__m_latch_69 = 0;
		__m_cycle_70.reset(samplerate, 0);
		__m_change_71.reset(0);
		__m_latch_72 = 0;
		__m_slide_73 = 0;
		__m_latch_76 = 0;
		__m_cycle_77.reset(samplerate, 0);
		__m_change_78.reset(0);
		__m_latch_79 = 0;
		__m_slide_80 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample history_13002_next_13007 = fixdenorm(((int)0));
		t_sample history_15837_next_15864 = fixdenorm(((t_sample)0.25));
		t_sample div_21071 = (m_knob_18 * ((t_sample)0.016666666666667));
		t_sample floor_21070 = floor(m_beats_16);
		t_sample div_21069 = safediv(div_21071, floor_21070);
		t_sample div_21056 = safediv(div_21069, samplerate);
		int iftrue_24 = (-10000000000);
		int int_10285 = int(m_button_19);
		t_sample iup_32 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_33 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_39 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_40 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_46 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_47 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_53 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_54 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_60 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_61 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_67 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_68 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_74 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_75 = (1 / maximum(1, abs(((int)0))));
		t_sample iup_81 = (1 / maximum(1, abs(((int)100))));
		t_sample idown_82 = (1 / maximum(1, abs(((int)0))));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample sub_13005 = (((int)0) - m_history_15);
			t_sample add_13006 = (((int)0) + m_history_15);
			t_sample div_13004 = safediv(sub_13005, add_13006);
			t_sample abs_13003 = fabs(div_13004);
			int gt_13001 = (abs_13003 > ((t_sample)0.5));
			int change_13000 = __m_change_20(gt_13001);
			int gt_12999 = (change_13000 > ((int)0));
			int gen_15852 = gt_12999;
			t_sample add_15853 = (((int)0) + m_history_12);
			t_sample sub_15840 = (add_15853 - ((int)0));
			t_sample round_15851 = (trunc((sub_15840 * ((t_sample)0.25))) * ((int)4));
			t_sample add_15841 = (round_15851 + ((int)0));
			t_sample sub_15862 = (m_history_13 - ((t_sample)0.25));
			t_sample add_15863 = (m_history_13 + ((t_sample)0.25));
			t_sample div_15861 = safediv(sub_15862, add_15863);
			t_sample abs_15835 = fabs(div_15861);
			int gt_15836 = (abs_15835 > ((t_sample)0.015625));
			int and_15839 = (gt_15836 && ((int)1));
			t_sample switch_15843 = (and_15839 ? and_15839 : m_history_14);
			t_sample switch_15846 = (gen_15852 ? switch_15843 : ((int)0));
			t_sample gen_15849 = switch_15846;
			t_sample switch_15845 = (switch_15846 ? ((int)0) : switch_15843);
			t_sample history_15847_next_15848 = fixdenorm(switch_15845);
			int or_15838 = (gen_15849 || ((int)0));
			t_sample switch_15857 = (or_15838 ? add_15841 : add_15853);
			t_sample wrap_15854 = wrap(switch_15857, ((int)0), ((int)1));
			t_sample gen_15866 = wrap_15854;
			t_sample history_15856_next_15865 = fixdenorm(wrap_15854);
			t_sample wrap_14619 = wrap(gen_15866, ((int)0), ((int)1));
			t_sample sub_33594 = (wrap_14619 - m_history_11);
			t_sample add_33599 = (wrap_14619 + m_history_11);
			t_sample div_33600 = safediv(sub_33594, add_33599);
			t_sample abs_33597 = fabs(div_33600);
			int gt_33593 = (abs_33597 > ((t_sample)0.5));
			int change_33598 = __m_change_21(gt_33593);
			int gt_33595 = (change_33598 > ((int)0));
			int gen_28319 = gt_33595;
			t_sample history_13002_next_33601 = fixdenorm(wrap_14619);
			t_sample sub_33603 = (gen_28319 - m_history_10);
			t_sample add_33609 = (gen_28319 + m_history_10);
			t_sample div_33610 = safediv(sub_33603, add_33609);
			t_sample abs_33611 = fabs(div_33610);
			int gt_33607 = (abs_33611 > ((t_sample)0.5));
			int change_33606 = __m_change_22(gt_33607);
			int gt_33604 = (change_33606 > ((int)0));
			int gen_13008 = gt_33604;
			t_sample history_13002_next_33608 = fixdenorm(gen_28319);
			t_sample plusequals_12998 = __m_pluseq_23.post(safediv(8, samplerate), gen_13008, 0);
			t_sample clamp_12997 = ((plusequals_12998 <= ((int)0)) ? ((int)0) : ((plusequals_12998 >= ((int)1)) ? ((int)1) : plusequals_12998));
			t_sample sub_34775 = (clamp_12997 - ((int)0));
			t_sample scale_34772 = ((safepow((sub_34775 * ((t_sample)1)), (1 * ((t_sample)0.25))) * ((int)-1)) + ((int)1));
			t_sample scale_13009 = scale_34772;
			t_sample sub_34779 = (scale_13009 - ((int)1));
			t_sample scale_34776 = ((safepow((sub_34779 * ((t_sample)-1)), ((int)1)) * ((int)-100)) + ((int)150));
			t_sample scale_13012 = scale_34776;
			t_sample sin_13013 = sin(scale_13012);
			t_sample mul_13014 = (scale_13009 * sin_13013);
			t_sample mix_34780 = (mul_13014 + (((t_sample)0.9) * (m_history_9 - mul_13014)));
			t_sample mix_13011 = mix_34780;
			t_sample gen_13016 = mix_13011;
			t_sample history_13010_next_13015 = fixdenorm(mix_13011);
			t_sample mul_25586 = (gen_13016 * ((t_sample)0.75));
			t_sample mul_18765 = (gen_13016 * ((t_sample)0.25));
			int or_20806 = (((int)0) || (elapsed == ((int)0)));
			t_sample switch_20807 = (or_20806 ? ((t_sample)0.1) : m_x_8);
			t_sample switch_20808 = (or_20806 ? ((t_sample)0.41) : m_y_7);
			t_sample mul_20821 = (switch_20808 * ((int)1));
			t_sample switch_20809 = (or_20806 ? ((t_sample)0.31) : m_z_6);
			t_sample mul_20826 = (switch_20809 * ((int)1));
			t_sample mul_20830 = (mul_20821 * ((t_sample)0.0002));
			t_sample add_20824 = (switch_20807 + mul_20830);
			t_sample fixnan_20810 = fixnan(add_20824);
			t_sample mul_20829 = (mul_20826 * ((t_sample)0.0002));
			t_sample add_20823 = (switch_20808 + mul_20829);
			t_sample fixnan_20812 = fixnan(add_20823);
			t_sample gen_33414 = fixnan_20812;
			t_sample mul_20818 = (switch_20809 * (-0.45));
			t_sample pow_20816 = safepow(switch_20807, ((int)3));
			t_sample mul_20817 = (pow_20816 * (-1));
			t_sample mul_20820 = (switch_20807 * ((t_sample)0.8));
			t_sample mul_20819 = (switch_20808 * (-1.1));
			t_sample add_20815 = (mul_20820 + mul_20819);
			t_sample add_20814 = (add_20815 + mul_20818);
			t_sample add_20813 = (add_20814 + mul_20817);
			t_sample mul_20828 = (add_20813 * ((t_sample)0.0002));
			t_sample add_20822 = (switch_20809 + mul_20828);
			t_sample fixnan_20811 = fixnan(add_20822);
			t_sample x_next_20831 = fixdenorm(fixnan_20810);
			t_sample y_next_20832 = fixdenorm(fixnan_20812);
			t_sample z_next_20833 = fixdenorm(fixnan_20811);
			t_sample elapsed_20838 = elapsed;
			int eq_20837 = (elapsed_20838 == ((int)0));
			int or_20845 = (eq_20837 || ((int)0));
			t_sample switch_20841 = (or_20845 ? ((int)10000000000) : m_history_5);
			t_sample min_20844 = ((switch_20841 < gen_33414) ? switch_20841 : gen_33414);
			t_sample gen_20848 = min_20844;
			t_sample switch_20840 = (or_20845 ? iftrue_24 : m_history_4);
			t_sample max_20843 = ((gen_33414 < switch_20840) ? switch_20840 : gen_33414);
			t_sample gen_20849 = max_20843;
			t_sample history_20839_next_20846 = fixdenorm(min_20844);
			t_sample history_20842_next_20847 = fixdenorm(max_20843);
			t_sample irange_34782 = (gen_20849 - gen_20848);
			t_sample sub_34784 = (gen_33414 - gen_20848);
			t_sample scale_34781 = ((safepow(safediv(sub_34784, irange_34782), ((int)1)) * ((int)2)) + ((int)-1));
			t_sample scale_20850 = scale_34781;
			t_sample gen_21066 = scale_20850;
			t_sample mul_21054 = (m_knob_17 * gen_21066);
			t_sample mul_21061 = (div_21056 * mul_21054);
			t_sample add_21055 = (div_21056 + mul_21061);
			t_sample add_21059 = (m_history_1 + add_21055);
			t_sample switch_21060 = (in2 ? ((int)0) : add_21059);
			t_sample wrap_21057 = wrap(switch_21060, ((int)0), ((int)1));
			t_sample bar_26869 = wrap_21057;
			t_sample mul_104 = (bar_26869 * ((int)8));
			t_sample floor_103 = floor(mul_104);
			int eq_93 = (floor_103 == ((int)1));
			int eq_75 = (floor_103 == ((int)3));
			int eq_48 = (floor_103 == ((int)7));
			int eq_66 = (floor_103 == ((int)5));
			int eq_102 = (floor_103 == ((int)0));
			int eq_84 = (floor_103 == ((int)2));
			int eq_57 = (floor_103 == ((int)6));
			int eq_39 = (floor_103 == ((int)4));
			t_sample noise_88 = noise();
			t_sample noise_70 = noise();
			t_sample noise_43 = noise();
			t_sample noise_61 = noise();
			t_sample noise_97 = noise();
			t_sample noise_79 = noise();
			t_sample noise_52 = noise();
			t_sample noise_27 = noise();
			int change_10286 = __m_change_25(int_10285);
			int eqp_10287 = ((int_10285 == change_10286) ? int_10285 : 0);
			int gen_10804 = eqp_10287;
			t_sample bar_29441 = bar_26869;
			t_sample sub_33613 = (bar_29441 - m_history_3);
			t_sample add_33621 = (bar_29441 + m_history_3);
			t_sample div_33620 = safediv(sub_33613, add_33621);
			t_sample abs_33616 = fabs(div_33620);
			int gt_33615 = (abs_33616 > ((t_sample)0.5));
			int change_33618 = __m_change_26(gt_33615);
			int gt_33614 = (change_33618 > ((int)0));
			int gen_29602 = gt_33614;
			t_sample history_13002_next_33619 = fixdenorm(bar_29441);
			t_sample switch_33627 = (gen_10804 ? gen_10804 : m_history_2);
			t_sample switch_33623 = (gen_29602 ? switch_33627 : ((int)0));
			t_sample gen_28480 = switch_33623;
			t_sample switch_33624 = (switch_33623 ? ((int)0) : switch_33627);
			t_sample history_15847_next_33626 = fixdenorm(switch_33624);
			__m_latch_27 = ((gen_28480 != 0) ? noise_61 : __m_latch_27);
			t_sample latch_58 = __m_latch_27;
			t_sample sub_34788 = (latch_58 - (-1));
			t_sample scale_34785 = ((safepow((sub_34788 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_59 = mtof(scale_34785, ((int)440));
			__m_cycle_28.freq(mtof_59);
			t_sample cycle_64 = __m_cycle_28(__sinedata);
			t_sample cycleindex_65 = __m_cycle_28.phase();
			int gt_33 = (cycle_64 > ((int)0));
			int change_32 = __m_change_29(gt_33);
			__m_latch_30 = ((change_32 != 0) ? eq_66 : __m_latch_30);
			int latch_31 = __m_latch_30;
			__m_slide_31 = fixdenorm((__m_slide_31 + (((latch_31 > __m_slide_31) ? iup_32 : idown_33) * (latch_31 - __m_slide_31))));
			t_sample slide_30 = __m_slide_31;
			t_sample mul_34 = (cycle_64 * slide_30);
			t_sample mul_11407 = (mul_34 * ((t_sample)0.25));
			__m_latch_34 = ((gen_28480 != 0) ? noise_88 : __m_latch_34);
			t_sample latch_85 = __m_latch_34;
			t_sample sub_34792 = (latch_85 - (-1));
			t_sample scale_34789 = ((safepow((sub_34792 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_86 = mtof(scale_34789, ((int)440));
			__m_cycle_35.freq(mtof_86);
			t_sample cycle_91 = __m_cycle_35(__sinedata);
			t_sample cycleindex_92 = __m_cycle_35.phase();
			int gt_33635 = (cycle_91 > ((int)0));
			int change_33630 = __m_change_36(gt_33635);
			__m_latch_37 = ((change_33630 != 0) ? eq_93 : __m_latch_37);
			int latch_33634 = __m_latch_37;
			__m_slide_38 = fixdenorm((__m_slide_38 + (((latch_33634 > __m_slide_38) ? iup_39 : idown_40) * (latch_33634 - __m_slide_38))));
			t_sample slide_33633 = __m_slide_38;
			t_sample mul_33631 = (cycle_91 * slide_33633);
			t_sample mul_11638 = (mul_33631 * ((t_sample)0.25));
			__m_latch_41 = ((gen_28480 != 0) ? noise_70 : __m_latch_41);
			t_sample latch_67 = __m_latch_41;
			t_sample sub_34796 = (latch_67 - (-1));
			t_sample scale_34793 = ((safepow((sub_34796 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_68 = mtof(scale_34793, ((int)440));
			__m_cycle_42.freq(mtof_68);
			t_sample cycle_73 = __m_cycle_42(__sinedata);
			t_sample cycleindex_74 = __m_cycle_42.phase();
			int gt_33642 = (cycle_73 > ((int)0));
			int change_33637 = __m_change_43(gt_33642);
			__m_latch_44 = ((change_33637 != 0) ? eq_75 : __m_latch_44);
			int latch_33641 = __m_latch_44;
			__m_slide_45 = fixdenorm((__m_slide_45 + (((latch_33641 > __m_slide_45) ? iup_46 : idown_47) * (latch_33641 - __m_slide_45))));
			t_sample slide_33640 = __m_slide_45;
			t_sample mul_33639 = (cycle_73 * slide_33640);
			t_sample mul_11636 = (mul_33639 * ((t_sample)0.25));
			__m_latch_48 = ((gen_28480 != 0) ? noise_43 : __m_latch_48);
			t_sample latch_40 = __m_latch_48;
			t_sample sub_34800 = (latch_40 - (-1));
			t_sample scale_34797 = ((safepow((sub_34800 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_41 = mtof(scale_34797, ((int)440));
			__m_cycle_49.freq(mtof_41);
			t_sample cycle_46 = __m_cycle_49(__sinedata);
			t_sample cycleindex_47 = __m_cycle_49.phase();
			int gt_33650 = (cycle_46 > ((int)0));
			int change_33647 = __m_change_50(gt_33650);
			__m_latch_51 = ((change_33647 != 0) ? eq_48 : __m_latch_51);
			int latch_33649 = __m_latch_51;
			__m_slide_52 = fixdenorm((__m_slide_52 + (((latch_33649 > __m_slide_52) ? iup_53 : idown_54) * (latch_33649 - __m_slide_52))));
			t_sample slide_33644 = __m_slide_52;
			t_sample mul_33648 = (cycle_46 * slide_33644);
			t_sample mul_11521 = (mul_33648 * ((t_sample)0.25));
			t_sample r_8615 = (((mul_11407 + mul_11521) + mul_11636) + mul_11638);
			t_sample sub_18309 = (r_8615 - mul_18765);
			t_sample out2 = (mul_25586 + sub_18309);
			__m_latch_55 = ((gen_28480 != 0) ? noise_97 : __m_latch_55);
			t_sample latch_94 = __m_latch_55;
			t_sample sub_34804 = (latch_94 - (-1));
			t_sample scale_34801 = ((safepow((sub_34804 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_95 = mtof(scale_34801, ((int)440));
			__m_cycle_56.freq(mtof_95);
			t_sample cycle_100 = __m_cycle_56(__sinedata);
			t_sample cycleindex_101 = __m_cycle_56.phase();
			int gt_33657 = (cycle_100 > ((int)0));
			int change_33654 = __m_change_57(gt_33657);
			__m_latch_58 = ((change_33654 != 0) ? eq_102 : __m_latch_58);
			int latch_33656 = __m_latch_58;
			__m_slide_59 = fixdenorm((__m_slide_59 + (((latch_33656 > __m_slide_59) ? iup_60 : idown_61) * (latch_33656 - __m_slide_59))));
			t_sample slide_33651 = __m_slide_59;
			t_sample mul_33655 = (cycle_100 * slide_33651);
			t_sample mul_11639 = (mul_33655 * ((t_sample)0.25));
			__m_latch_62 = ((gen_28480 != 0) ? noise_79 : __m_latch_62);
			t_sample latch_76 = __m_latch_62;
			t_sample sub_34808 = (latch_76 - (-1));
			t_sample scale_34805 = ((safepow((sub_34808 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_77 = mtof(scale_34805, ((int)440));
			__m_cycle_63.freq(mtof_77);
			t_sample cycle_82 = __m_cycle_63(__sinedata);
			t_sample cycleindex_83 = __m_cycle_63.phase();
			int gt_33664 = (cycle_82 > ((int)0));
			int change_33661 = __m_change_64(gt_33664);
			__m_latch_65 = ((change_33661 != 0) ? eq_84 : __m_latch_65);
			int latch_33663 = __m_latch_65;
			__m_slide_66 = fixdenorm((__m_slide_66 + (((latch_33663 > __m_slide_66) ? iup_67 : idown_68) * (latch_33663 - __m_slide_66))));
			t_sample slide_33658 = __m_slide_66;
			t_sample mul_33662 = (cycle_82 * slide_33658);
			t_sample mul_11637 = (mul_33662 * ((t_sample)0.25));
			__m_latch_69 = ((gen_28480 != 0) ? noise_52 : __m_latch_69);
			t_sample latch_49 = __m_latch_69;
			t_sample sub_34812 = (latch_49 - (-1));
			t_sample scale_34809 = ((safepow((sub_34812 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_50 = mtof(scale_34809, ((int)440));
			__m_cycle_70.freq(mtof_50);
			t_sample cycle_55 = __m_cycle_70(__sinedata);
			t_sample cycleindex_56 = __m_cycle_70.phase();
			int gt_33671 = (cycle_55 > ((int)0));
			int change_33668 = __m_change_71(gt_33671);
			__m_latch_72 = ((change_33668 != 0) ? eq_57 : __m_latch_72);
			int latch_33670 = __m_latch_72;
			__m_slide_73 = fixdenorm((__m_slide_73 + (((latch_33670 > __m_slide_73) ? iup_74 : idown_75) * (latch_33670 - __m_slide_73))));
			t_sample slide_33665 = __m_slide_73;
			t_sample mul_33669 = (cycle_55 * slide_33665);
			t_sample mul_11522 = (mul_33669 * ((t_sample)0.25));
			__m_latch_76 = ((gen_28480 != 0) ? noise_27 : __m_latch_76);
			t_sample latch_24 = __m_latch_76;
			t_sample sub_34816 = (latch_24 - (-1));
			t_sample scale_34813 = ((safepow((sub_34816 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_25 = mtof(scale_34813, ((int)440));
			__m_cycle_77.freq(mtof_25);
			t_sample cycle_37 = __m_cycle_77(__sinedata);
			t_sample cycleindex_38 = __m_cycle_77.phase();
			int gt_33678 = (cycle_37 > ((int)0));
			int change_33675 = __m_change_78(gt_33678);
			__m_latch_79 = ((change_33675 != 0) ? eq_39 : __m_latch_79);
			int latch_33677 = __m_latch_79;
			__m_slide_80 = fixdenorm((__m_slide_80 + (((latch_33677 > __m_slide_80) ? iup_81 : idown_82) * (latch_33677 - __m_slide_80))));
			t_sample slide_33672 = __m_slide_80;
			t_sample mul_33676 = (cycle_37 * slide_33672);
			t_sample mul_11293 = (mul_33676 * ((t_sample)0.25));
			t_sample l_8614 = (((mul_11293 + mul_11522) + mul_11637) + mul_11639);
			t_sample sub_18461 = (l_8614 - mul_18765);
			t_sample out1 = (mul_25586 + sub_18461);
			t_sample history_21058_next_33679 = fixdenorm(wrap_21057);
			m_history_15 = history_13002_next_13007;
			m_history_12 = history_15856_next_15865;
			m_history_13 = history_15837_next_15864;
			m_history_14 = history_15847_next_15848;
			m_history_11 = history_13002_next_33601;
			m_history_10 = history_13002_next_33608;
			m_history_9 = history_13010_next_13015;
			m_x_8 = x_next_20831;
			m_z_6 = z_next_20833;
			m_y_7 = y_next_20832;
			m_history_5 = history_20839_next_20846;
			m_history_4 = history_20842_next_20847;
			m_history_3 = history_13002_next_33619;
			m_history_2 = history_15847_next_33626;
			m_history_1 = history_21058_next_33679;
			(elapsed++);
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_beats(t_param _value) {
		m_beats_16 = (_value < 1 ? 1 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2(t_param _value) {
		m_knob_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob1(t_param _value) {
		m_knob_18 = (_value < 40 ? 40 : (_value > 200 ? 200 : _value));
	};
	inline void set_button(t_param _value) {
		m_button_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 4; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "reset" };
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
		case 0: self->set_beats(value); break;
		case 1: self->set_button(value); break;
		case 2: self->set_knob1(value); break;
		case 3: self->set_knob2(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_beats_16; break;
		case 1: *value = self->m_button_19; break;
		case 2: *value = self->m_knob_18; break;
		case 3: *value = self->m_knob_17; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(4 * sizeof(ParamInfo));
	self->__commonstate.numparams = 4;
	// initialize parameter 0 ("m_beats_16")
	pi = self->__commonstate.params + 0;
	pi->name = "beats";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_beats_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_button_19")
	pi = self->__commonstate.params + 1;
	pi->name = "button";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_button_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob_18")
	pi = self->__commonstate.params + 2;
	pi->name = "knob1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 40;
	pi->outputmax = 200;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob_17")
	pi = self->__commonstate.params + 3;
	pi->name = "knob2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
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


} // daisy_2dtechno_2dmachine_2dchaos_2dtime::
