#include "simply_2doopsy.h"

namespace simply_2doopsy {

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
	Delay m_delay_15;
	Delay m_delay_9;
	Delay m_delay_8;
	Delay m_delay_7;
	Delay m_delay_10;
	Delay m_delay_12;
	Delay m_delay_11;
	Delay m_delay_13;
	Delay m_delay_14;
	Delay m_delay_6;
	Delay m_delay_4;
	Delay m_delay_16;
	Delay m_delay_5;
	SineCycle __m_cycle_29;
	SineCycle __m_cycle_28;
	SineCycle __m_cycle_27;
	SineCycle __m_cycle_26;
	SineCycle __m_cycle_30;
	SineCycle __m_cycle_31;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample m_history_2;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample m_damping_25;
	t_sample m_history_3;
	t_sample m_decaydiffusion_24;
	t_sample m_indiffusion_22;
	t_sample m_indiffusion_18;
	t_sample m_inbandwidth_23;
	t_sample m_predelay_19;
	t_sample m_decaydiffusion_21;
	t_sample m_decay_20;
	t_sample m_drywet_17;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_delay_4.reset("m_delay_4", ((int)688));
		m_delay_5.reset("m_delay_5", ((int)924));
		m_delay_6.reset("m_delay_6", ((int)3720));
		m_delay_7.reset("m_delay_7", ((int)4453));
		m_delay_8.reset("m_delay_8", ((int)2656));
		m_delay_9.reset("m_delay_9", ((int)1800));
		m_delay_10.reset("m_delay_10", ((int)4217));
		m_delay_11.reset("m_delay_11", ((int)3163));
		m_delay_12.reset("m_delay_12", ((int)142));
		m_delay_13.reset("m_delay_13", ((int)107));
		m_delay_14.reset("m_delay_14", ((int)379));
		m_delay_15.reset("m_delay_15", ((int)277));
		m_delay_16.reset("m_delay_16", (samplerate * 0.1));
		m_drywet_17 = ((t_sample)0.5);
		m_indiffusion_18 = ((t_sample)0.625);
		m_predelay_19 = ((int)10);
		m_decay_20 = ((t_sample)0.5);
		m_decaydiffusion_21 = ((t_sample)0.5);
		m_indiffusion_22 = ((t_sample)0.75);
		m_inbandwidth_23 = ((t_sample)0.5);
		m_decaydiffusion_24 = ((t_sample)0.7);
		m_damping_25 = ((t_sample)0.5);
		__m_cycle_26.reset(samplerate, 0);
		__m_cycle_27.reset(samplerate, 0);
		__m_cycle_28.reset(samplerate, 0);
		__m_cycle_29.reset(samplerate, 0);
		__m_cycle_30.reset(samplerate, 0);
		__m_cycle_31.reset(samplerate, 0);
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
		t_sample mstosamps_1010 = (m_predelay_19 * (samplerate * 0.001));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			__m_cycle_26.freq(((int)880));
			t_sample cycle_565 = __m_cycle_26(__sinedata);
			t_sample cycleindex_566 = __m_cycle_26.phase();
			__m_cycle_27.freq(((int)330));
			t_sample cycle_561 = __m_cycle_27(__sinedata);
			t_sample cycleindex_562 = __m_cycle_27.phase();
			__m_cycle_28.freq(((int)440));
			t_sample cycle_563 = __m_cycle_28(__sinedata);
			t_sample cycleindex_564 = __m_cycle_28.phase();
			__m_cycle_29.freq(((int)220));
			t_sample cycle_559 = __m_cycle_29(__sinedata);
			t_sample cycleindex_560 = __m_cycle_29.phase();
			t_sample tap_1039 = m_delay_16.read_linear(mstosamps_1010);
			t_sample mix_1494 = (m_history_1 + (m_inbandwidth_23 * (tap_1039 - m_history_1)));
			t_sample mix_1037 = mix_1494;
			t_sample tap_1016 = m_delay_15.read_step(((int)277));
			t_sample mul_1014 = (tap_1016 * m_indiffusion_18);
			t_sample tap_1022 = m_delay_14.read_step(((int)379));
			t_sample mul_1020 = (tap_1022 * m_indiffusion_18);
			t_sample tap_1028 = m_delay_13.read_step(((int)107));
			t_sample mul_1026 = (tap_1028 * m_indiffusion_22);
			t_sample tap_1034 = m_delay_12.read_step(((int)142));
			t_sample mul_1032 = (tap_1034 * m_indiffusion_22);
			t_sample sub_1030 = (mix_1037 - mul_1032);
			t_sample mul_1031 = (sub_1030 * m_indiffusion_22);
			t_sample add_1029 = (mul_1031 + tap_1034);
			t_sample sub_1024 = (add_1029 - mul_1026);
			t_sample mul_1025 = (sub_1024 * m_indiffusion_22);
			t_sample add_1023 = (mul_1025 + tap_1028);
			t_sample sub_1018 = (add_1023 - mul_1020);
			t_sample mul_1019 = (sub_1018 * m_indiffusion_18);
			t_sample add_1017 = (mul_1019 + tap_1022);
			t_sample sub_1012 = (add_1017 - mul_1014);
			t_sample mul_1013 = (sub_1012 * m_indiffusion_18);
			t_sample add_1011 = (mul_1013 + tap_1016);
			t_sample tap_945 = m_delay_11.read_step(((int)3163));
			t_sample tap_946 = m_delay_11.read_step(((int)121));
			t_sample tap_947 = m_delay_11.read_step(((int)1996));
			t_sample tap_957 = m_delay_10.read_step(((int)4217));
			t_sample tap_958 = m_delay_10.read_step(((int)266));
			t_sample tap_959 = m_delay_10.read_step(((int)2974));
			t_sample tap_960 = m_delay_10.read_step(((int)2111));
			t_sample gen_1006 = ((tap_958 + tap_959) + tap_947);
			t_sample tap_981 = m_delay_9.read_step(((int)1800));
			t_sample tap_982 = m_delay_9.read_step(((int)187));
			t_sample tap_983 = m_delay_9.read_step(((int)1228));
			t_sample tap_953 = m_delay_8.read_step(((int)2656));
			t_sample tap_954 = m_delay_8.read_step(((int)335));
			t_sample tap_955 = m_delay_8.read_step(((int)1913));
			t_sample gen_1009 = (((tap_960 + tap_954) + tap_946) + tap_983);
			t_sample tap_988 = m_delay_7.read_step(((int)4453));
			t_sample tap_989 = m_delay_7.read_step(((int)353));
			t_sample tap_990 = m_delay_7.read_step(((int)3627));
			t_sample tap_991 = m_delay_7.read_step(((int)1990));
			t_sample tap_973 = m_delay_6.read_step(((int)3720));
			t_sample tap_974 = m_delay_6.read_step(((int)1066));
			t_sample tap_975 = m_delay_6.read_step(((int)2673));
			t_sample gen_1007 = (((tap_955 + tap_974) + tap_982) + tap_991);
			t_sample gen_1008 = ((tap_975 + tap_989) + tap_990);
			t_sample mix_1495 = (tap_957 + (m_damping_25 * (m_history_3 - tap_957)));
			t_sample mix_942 = mix_1495;
			t_sample mix_1496 = (tap_988 + (m_damping_25 * (m_history_2 - tap_988)));
			t_sample mix_986 = mix_1496;
			t_sample mul_977 = (tap_981 * m_decaydiffusion_21);
			t_sample mul_949 = (tap_953 * m_decaydiffusion_21);
			t_sample mul_984 = (mix_986 * m_decay_20);
			t_sample sub_978 = (mul_984 - mul_977);
			t_sample mul_976 = (sub_978 * m_decaydiffusion_21);
			t_sample add_979 = (mul_976 + tap_981);
			t_sample mul_940 = (mix_942 * m_decay_20);
			t_sample sub_950 = (mul_940 - mul_949);
			t_sample mul_948 = (sub_950 * m_decaydiffusion_21);
			t_sample add_951 = (mul_948 + tap_953);
			t_sample mul_971 = (tap_973 * m_decay_20);
			t_sample add_1002 = (mul_971 + add_1011);
			__m_cycle_30.freq(((t_sample)0.07));
			t_sample cycle_961 = __m_cycle_30(__sinedata);
			t_sample cycleindex_962 = __m_cycle_30.phase();
			t_sample mul_963 = (cycle_961 * ((int)16));
			t_sample add_964 = (mul_963 + ((int)908));
			t_sample tap_970 = m_delay_5.read_linear(add_964);
			t_sample mul_966 = (tap_970 * m_decaydiffusion_24);
			t_sample add_967 = (add_1002 + mul_966);
			t_sample mul_965 = (add_967 * m_decaydiffusion_24);
			t_sample rsub_968 = (tap_970 - mul_965);
			t_sample mul_943 = (tap_945 * m_decay_20);
			t_sample add_1003 = (add_1011 + mul_943);
			__m_cycle_31.freq(((t_sample)0.1));
			t_sample cycle_992 = __m_cycle_31(__sinedata);
			t_sample cycleindex_993 = __m_cycle_31.phase();
			t_sample mul_994 = (cycle_992 * ((int)16));
			t_sample add_995 = (mul_994 + ((int)672));
			t_sample tap_1001 = m_delay_4.read_linear(add_995);
			t_sample mul_997 = (tap_1001 * m_decaydiffusion_24);
			t_sample add_998 = (add_1003 + mul_997);
			t_sample mul_996 = (add_998 * m_decaydiffusion_24);
			t_sample rsub_999 = (tap_1001 - mul_996);
			t_sample history_941_next_1004 = fixdenorm(mix_942);
			t_sample history_985_next_1005 = fixdenorm(mix_986);
			t_sample sub_925 = (gen_1006 - gen_1007);
			t_sample mul_923 = (sub_925 * ((t_sample)0.6));
			t_sample mix_1497 = (cycle_565 + (m_drywet_17 * (mul_923 - cycle_565)));
			t_sample out1 = mix_1497;
			t_sample sub_924 = (gen_1008 - gen_1009);
			t_sample mul_922 = (sub_924 * ((t_sample)0.6));
			t_sample mix_1498 = (cycle_561 + (m_drywet_17 * (mul_922 - cycle_561)));
			t_sample out2 = mix_1498;
			t_sample history_1036_next_1442 = fixdenorm(mix_1037);
			m_delay_16.write((((cycle_559 + cycle_563) + cycle_561) + cycle_565));
			m_delay_15.write(sub_1012);
			m_delay_12.write(sub_1030);
			m_delay_13.write(sub_1024);
			m_delay_14.write(sub_1018);
			m_delay_11.write(add_951);
			m_history_2 = history_985_next_1005;
			m_history_3 = history_941_next_1004;
			m_delay_4.write(add_998);
			m_delay_5.write(add_967);
			m_delay_6.write(add_979);
			m_delay_7.write(rsub_999);
			m_delay_8.write(sub_950);
			m_delay_9.write(sub_978);
			m_delay_10.write(rsub_968);
			m_history_1 = history_1036_next_1442;
			m_delay_4.step();
			m_delay_5.step();
			m_delay_6.step();
			m_delay_7.step();
			m_delay_8.step();
			m_delay_9.step();
			m_delay_10.step();
			m_delay_11.step();
			m_delay_12.step();
			m_delay_13.step();
			m_delay_14.step();
			m_delay_15.step();
			m_delay_16.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_drywet(t_param _value) {
		m_drywet_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_indiffusion2(t_param _value) {
		m_indiffusion_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_predelay(t_param _value) {
		m_predelay_19 = (_value < 0 ? 0 : (_value > 100 ? 100 : _value));
	};
	inline void set_decay(t_param _value) {
		m_decay_20 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_decaydiffusion2(t_param _value) {
		m_decaydiffusion_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_indiffusion1(t_param _value) {
		m_indiffusion_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_inbandwidth(t_param _value) {
		m_inbandwidth_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_decaydiffusion1(t_param _value) {
		m_decaydiffusion_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_damping(t_param _value) {
		m_damping_25 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
int num_params() { return 9; }

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
		case 0: self->set_damping(value); break;
		case 1: self->set_decay(value); break;
		case 2: self->set_decaydiffusion1(value); break;
		case 3: self->set_decaydiffusion2(value); break;
		case 4: self->set_drywet(value); break;
		case 5: self->set_inbandwidth(value); break;
		case 6: self->set_indiffusion1(value); break;
		case 7: self->set_indiffusion2(value); break;
		case 8: self->set_predelay(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_damping_25; break;
		case 1: *value = self->m_decay_20; break;
		case 2: *value = self->m_decaydiffusion_24; break;
		case 3: *value = self->m_decaydiffusion_21; break;
		case 4: *value = self->m_drywet_17; break;
		case 5: *value = self->m_inbandwidth_23; break;
		case 6: *value = self->m_indiffusion_22; break;
		case 7: *value = self->m_indiffusion_18; break;
		case 8: *value = self->m_predelay_19; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(9 * sizeof(ParamInfo));
	self->__commonstate.numparams = 9;
	// initialize parameter 0 ("m_damping_25")
	pi = self->__commonstate.params + 0;
	pi->name = "damping";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_damping_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_decay_20")
	pi = self->__commonstate.params + 1;
	pi->name = "decay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_decay_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_decaydiffusion_24")
	pi = self->__commonstate.params + 2;
	pi->name = "decaydiffusion1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_decaydiffusion_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_decaydiffusion_21")
	pi = self->__commonstate.params + 3;
	pi->name = "decaydiffusion2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_decaydiffusion_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_drywet_17")
	pi = self->__commonstate.params + 4;
	pi->name = "drywet";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_drywet_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_inbandwidth_23")
	pi = self->__commonstate.params + 5;
	pi->name = "inbandwidth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_inbandwidth_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_indiffusion_22")
	pi = self->__commonstate.params + 6;
	pi->name = "indiffusion1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_indiffusion_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_indiffusion_18")
	pi = self->__commonstate.params + 7;
	pi->name = "indiffusion2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_indiffusion_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_predelay_19")
	pi = self->__commonstate.params + 8;
	pi->name = "predelay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_predelay_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 100;
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


} // simply_2doopsy::
