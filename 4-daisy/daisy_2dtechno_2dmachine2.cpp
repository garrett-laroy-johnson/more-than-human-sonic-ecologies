#include "daisy_2dtechno_2dmachine2.h"

namespace daisy_2dtechno_2dmachine2 {

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
	Change __m_change_28;
	Change __m_change_23;
	Change __m_change_22;
	Change __m_change_20;
	Change __m_change_14;
	Data m_notes_13;
	Delta __m_delta_21;
	Phasor __m_phasor_19;
	PlusEquals __m_pluseq_15;
	PlusEquals __m_pluseq_24;
	SineCycle __m_cycle_27;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample m_history_3;
	t_sample m_knob_11;
	t_sample m_history_2;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample m_history_4;
	t_sample m_history_10;
	t_sample m_history_5;
	t_sample __m_latch_16;
	t_sample m_history_9;
	t_sample samples_to_seconds;
	t_sample m_history_8;
	t_sample m_history_6;
	t_sample m_history_7;
	t_sample m_button_12;
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
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		m_knob_11 = ((int)0);
		m_button_12 = ((int)0);
		m_notes_13.reset("notes", ((int)512), ((int)1));
		__m_change_14.reset(0);
		__m_pluseq_15.reset(0);
		__m_latch_16 = 0;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_19.reset(0);
		__m_change_20.reset(0);
		__m_delta_21.reset(0);
		__m_change_22.reset(0);
		__m_change_23.reset(0);
		__m_pluseq_24.reset(0);
		__m_cycle_27.reset(samplerate, 0);
		__m_change_28.reset(0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		const t_sample * __in3 = __ins[2];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__in3 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		int int_9824 = int(m_button_12);
		int notes_dim = m_notes_13.dim;
		int notes_channels = m_notes_13.channels;
		samples_to_seconds = (1 / samplerate);
		t_sample history_9768_next_9804 = fixdenorm(((t_sample)0.5));
		t_sample mul_9745 = (samplerate * (2 * ((t_sample)0.33333333333333)));
		t_sample t_9746 = exp(safediv(-6.9077552789821, mul_9745));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			const t_sample in3 = (*(__in3++));
			int lt_9868 = (m_history_1 < ((int)9));
			int change_9825 = __m_change_14(int_9824);
			int eqp_9826 = ((int_9824 == change_9825) ? int_9824 : 0);
			int gen_9827 = eqp_9826;
			t_sample plusequals_9755 = __m_pluseq_15.post(lt_9868, (gen_9827 + in3), 0);
			t_sample sub_9904 = (plusequals_9755 - ((int)1));
			t_sample noise_9761 = noise();
			__m_latch_16 = ((plusequals_9755 != 0) ? noise_9761 : __m_latch_16);
			t_sample latch_9758 = __m_latch_16;
			t_sample sub_10097 = (latch_9758 - (-1));
			t_sample scale_10094 = ((safepow((sub_10097 * ((t_sample)0.5)), ((int)1)) * ((int)12)) + ((int)60));
			t_sample mtof_9759 = mtof(scale_10094, ((int)440));
			int index_trunc_17 = fixnan(floor(sub_9904));
			bool index_ignore_18 = ((index_trunc_17 >= notes_dim) || (index_trunc_17 < 0));
			if ((!index_ignore_18)) {
				m_notes_13.write(mtof_9759, index_trunc_17, 0);
				
			};
			t_sample phasor_9832 = __m_phasor_19(((t_sample)0.83333333333333), samples_to_seconds);
			t_sample mul_9773 = (phasor_9832 * ((int)2));
			t_sample sub_9789 = (phasor_9832 - m_history_10);
			t_sample add_9790 = (phasor_9832 + m_history_10);
			t_sample div_9788 = safediv(sub_9789, add_9790);
			t_sample abs_9787 = fabs(div_9788);
			int gt_9785 = (abs_9787 > ((t_sample)0.5));
			int change_9784 = __m_change_20(gt_9785);
			int gt_9783 = (change_9784 > ((int)0));
			int gen_9792 = gt_9783;
			t_sample history_9786_next_9791 = fixdenorm(phasor_9832);
			t_sample delta_9798 = __m_delta_21(phasor_9832);
			t_sample wrap_9799 = wrap(delta_9798, (-0.5), ((t_sample)0.5));
			t_sample gen_9800 = wrap_9799;
			t_sample mul_9795 = (gen_9800 * ((int)2));
			t_sample add_9793 = (mul_9795 + m_history_7);
			t_sample sub_9771 = (add_9793 - mul_9773);
			t_sample round_9782 = (trunc((sub_9771 * ((t_sample)0.5))) * ((int)2));
			t_sample add_9772 = (round_9782 + mul_9773);
			t_sample sub_9802 = (m_history_8 - ((t_sample)0.5));
			t_sample add_9803 = (m_history_8 + ((t_sample)0.5));
			t_sample div_9801 = safediv(sub_9802, add_9803);
			t_sample abs_9766 = fabs(div_9801);
			int gt_9767 = (abs_9766 > ((t_sample)0.015625));
			int and_9770 = (gt_9767 && ((int)1));
			t_sample switch_9774 = (and_9770 ? and_9770 : m_history_9);
			t_sample switch_9777 = (gen_9792 ? switch_9774 : ((int)0));
			t_sample gen_9780 = switch_9777;
			t_sample switch_9776 = (switch_9777 ? ((int)0) : switch_9774);
			t_sample history_9778_next_9779 = fixdenorm(switch_9776);
			int or_9769 = (gen_9780 || ((int)0));
			t_sample switch_9797 = (or_9769 ? add_9772 : add_9793);
			t_sample wrap_9794 = wrap(switch_9797, ((int)0), ((int)1));
			t_sample gen_9806 = wrap_9794;
			t_sample history_9796_next_9805 = fixdenorm(wrap_9794);
			t_sample wrap_9808 = wrap(gen_9806, ((int)0), ((int)1));
			t_sample sub_10049 = (wrap_9808 - m_history_6);
			t_sample add_10046 = (wrap_9808 + m_history_6);
			t_sample div_10053 = safediv(sub_10049, add_10046);
			t_sample abs_10047 = fabs(div_10053);
			int gt_10050 = (abs_10047 > ((t_sample)0.5));
			int change_10051 = __m_change_22(gt_10050);
			int gt_10045 = (change_10051 > ((int)0));
			int gen_9807 = gt_10045;
			t_sample history_9786_next_10052 = fixdenorm(wrap_9808);
			t_sample sub_10056 = (gen_9807 - m_history_5);
			t_sample add_10061 = (gen_9807 + m_history_5);
			t_sample div_10063 = safediv(sub_10056, add_10061);
			t_sample abs_10059 = fabs(div_10063);
			int gt_10060 = (abs_10059 > ((t_sample)0.5));
			int change_10062 = __m_change_23(gt_10060);
			int gt_10055 = (change_10062 > ((int)0));
			int gen_9813 = gt_10055;
			t_sample history_9786_next_10058 = fixdenorm(gen_9807);
			t_sample plusequals_9812 = __m_pluseq_24.post(safediv(8, samplerate), gen_9813, 0);
			t_sample clamp_9811 = ((plusequals_9812 <= ((int)0)) ? ((int)0) : ((plusequals_9812 >= ((int)1)) ? ((int)1) : plusequals_9812));
			t_sample sub_10101 = (clamp_9811 - ((int)0));
			t_sample scale_10098 = ((safepow((sub_10101 * ((t_sample)1)), (1 * ((t_sample)0.25))) * ((int)-1)) + ((int)1));
			t_sample scale_9814 = scale_10098;
			t_sample sub_10105 = (scale_9814 - ((int)1));
			t_sample scale_10102 = ((safepow((sub_10105 * ((t_sample)-1)), ((int)1)) * ((int)-100)) + ((int)150));
			t_sample scale_9817 = scale_10102;
			t_sample sin_9818 = sin(scale_9817);
			t_sample mul_9819 = (scale_9814 * sin_9818);
			t_sample mix_10106 = (mul_9819 + (((t_sample)0.9) * (m_history_4 - mul_9819)));
			t_sample mix_9816 = mix_10106;
			t_sample gen_9821 = mix_9816;
			t_sample history_9815_next_9820 = fixdenorm(mix_9816);
			t_sample mul_9810 = (gen_9821 * ((t_sample)0.5));
			t_sample mul_9831 = (phasor_9832 * ((int)8));
			t_sample floor_9830 = floor(mul_9831);
			int index_trunc_25 = fixnan(floor(floor_9830));
			bool index_ignore_26 = ((index_trunc_25 >= notes_dim) || (index_trunc_25 < 0));
			// samples notes channel 1;
			t_sample sample_notes_9756 = (index_ignore_26 ? 0 : m_notes_13.read(index_trunc_25, 0));
			t_sample index_notes_9757 = floor_9830;
			__m_cycle_27.freq(sample_notes_9756);
			t_sample cycle_9828 = __m_cycle_27(__sinedata);
			t_sample cycleindex_9829 = __m_cycle_27.phase();
			int change_9752 = __m_change_28(floor_9830);
			int abs_9750 = abs(change_9752);
			int gt_9751 = (abs_9750 > ((t_sample)0.5));
			t_sample mul_9744 = ((m_history_3 + gt_9751) * t_9746);
			t_sample clamp_9740 = ((mul_9744 <= ((int)0)) ? ((int)0) : ((mul_9744 >= ((int)1)) ? ((int)1) : mul_9744));
			t_sample mix_10107 = (clamp_9740 + (((t_sample)0.97) * (m_history_2 - clamp_9740)));
			t_sample mix_9742 = mix_10107;
			t_sample gen_9749 = mix_9742;
			t_sample history_9743_next_9747 = fixdenorm(clamp_9740);
			t_sample history_9741_next_9748 = fixdenorm(mix_9742);
			t_sample mul_9739 = (gen_9749 * cycle_9828);
			t_sample mul_9823 = (mul_9739 * ((int)1));
			t_sample out1 = (mul_9823 + mul_9810);
			t_sample out2 = (mul_9823 + mul_9810);
			t_sample history_9753_next_10065 = fixdenorm(plusequals_9755);
			m_history_10 = history_9786_next_9791;
			m_history_7 = history_9796_next_9805;
			m_history_8 = history_9768_next_9804;
			m_history_9 = history_9778_next_9779;
			m_history_6 = history_9786_next_10052;
			m_history_5 = history_9786_next_10058;
			m_history_4 = history_9815_next_9820;
			m_history_3 = history_9743_next_9747;
			m_history_2 = history_9741_next_9748;
			m_history_1 = history_9753_next_10065;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_knob1(t_param _value) {
		m_knob_11 = (_value < 40 ? 40 : (_value > 200 ? 200 : _value));
	};
	inline void set_button(t_param _value) {
		m_button_12 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_notes(void * _value) {
		m_notes_13.setbuffer(_value);
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 3;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 3; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2", "in3" };
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
		case 2: self->set_notes(ref); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_button_12; break;
		case 1: *value = self->m_knob_11; break;
		
		
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
	// initialize parameter 0 ("m_button_12")
	pi = self->__commonstate.params + 0;
	pi->name = "button";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_button_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob_11")
	pi = self->__commonstate.params + 1;
	pi->name = "knob1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 40;
	pi->outputmax = 200;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_notes_13")
	pi = self->__commonstate.params + 2;
	pi->name = "notes";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
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


} // daisy_2dtechno_2dmachine2::
