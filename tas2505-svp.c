#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/pm_runtime.h>
#include <linux/regmap.h>
//#include <linux/slab.h>
//#include <linux/regulator/consumer.h>
//#include <linux/delay.h>

//#include <sound/pcm.h>
//#include <sound/pcm_params.h>
#include <sound/soc.h>
//#include <sound/soc-dapm.h>
//#include <sound/tlv.h>

#include "tas2505-svp.h"
struct tas5720_data {
	struct snd_soc_component *component;
	struct regmap *regmap;
	struct i2c_client *tas5720_client;
};

/*** BEGIN:  DEV SOC COMPONENT ***/
static int tas2505_codec_probe(struct snd_soc_component *component) {

    /* Read Page Register just to check if I2C is working */
    /* TODO: Set the device to mute*/
    /* TODO: Enter shutdown mode */
    return 0;

}


static const  struct  snd_soc_component_driver  soc_component_dev_tas2505 = {
    .probe = tas2505_codec_probe,
};
 
/*** END:  DEV SOC COMPONENT  ***/


/*** BEGIN:  SOC DAI Config ***/
static const struct  snd_soc_dai_ops tas2505_speaker_dai_ops = {
    
};
 
static struct snd_soc_dai_driver tas2520_dai[] = {
    {
		.name = "tas2505-amplifier",
		.playback = {
			.stream_name	= "Playback",
			.channels_min	= 1,
			.channels_max	= 2,
			.rates		= TAS2505_RATES,
			.formats	= TAS2505_FORMATS,
		},
		.ops = &tas2505_speaker_dai_ops,
		.symmetric_rates = 1,
	},

};
/*** END:  RSOC DAI Config  ***/


/*** BEGIN:  REGMAP Configuration ***/

static bool tas2505_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case TAS2505_PAGECTL:
	case TAS2505_RESET:
		return true;
	default:
		return false;
	}
};

static const struct regmap_config tas2505_regmap_config = {
    .reg_bits = 8,
    .val_bits = 8,
    .max_register = 69*128,
    .cache_type = REGCACHE_RBTREE, 
    .volatile_reg = tas2505_is_volatile_reg,
};

/*** END:  REGMAP Configuration ***/

/*** BEGIN:  I2C PROBE ***/

static int tas2505_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
    struct device *dev = &client->dev;
    struct tas5720_data *data;
	const struct regmap_config *regmap_config;
	int ret;

    /* Alocated memory for the device */
    data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;
    
    data->tas5720_client = client;

    /* Configuration of REGMAP for I2C device*/
    regmap_config = &tas2505_regmap_config;
    data->regmap = devm_regmap_init_i2c(client, regmap_config);
    if (IS_ERR(data->regmap)) {
        ret = PTR_ERR(data->regmap);
        dev_err(dev, "failed to allocate register map: %d\n", ret);
		return ret;
    }

    dev_set_drvdata(dev, data);

    /* Register a component with automatic unregistration when the device is
    * unregistered.
    */
    ret = devm_snd_soc_register_component(&client->dev,
                &soc_component_dev_tas2505,
                tas2520_dai,
                ARRAY_SIZE(tas2520_dai));
    
    if (ret < 0) {
		dev_err(dev, "failed to register component: %d\n", ret);
		return ret;
	}
    
    return 0;
}

/*** END:  I2C PROBE ***/


/*** BEGIN:  Driver and device binding ***/

static const struct i2c_device_id tas2505_id [] = {
    {"tas2505", 0}
};
MODULE_DEVICE_TABLE(i2ic, tas2505_id);

#if IS_ENABLED(CONFIG_OF)
static const struct of_device_id tas2505_of_match[] = {
	{ .compatible = "ti,tas2505", },
	{ },
};
MODULE_DEVICE_TABLE(of, tas2505_of_match);
#endif

static struct i2c_driver tas2505_i2c_driver = {
    .driver = {
        .name = "tas2505", 
        .of_match_table = of_match_ptr(tas2505_of_match), 
    },
    .probe = tas2505_probe, //new version of probe
    .id_table = tas2505_id
};

module_i2c_driver(tas2505_i2c_driver);

/*** END:  Driver and device binding ***/


MODULE_AUTHOR("Jose Igor Moreira <jose.igor.moreira.ext@europe.svpworldwide.com>");
MODULE_DESCRIPTION("TAS2505 Audio amplifier driver : SVP version");
MODULE_LICENSE("Dual BSD/GPL");
